#include "KSTrajTermMovingSurfaceUCN.h"

#include "KConst.h"
#include "KRandom.h"

namespace Kassiopeia
{

// Global Variables for UCN reflection
double fTanThetaIn;
double fExpThetaCoef;

KSTrajTermMovingSurfaceUCN::KSTrajTermMovingSurfaceUCN() :
  fTheta(0.),
  fPhi(0.),
  fValueFormula("x"),
  fValueMin(0.),
  fValueMax(0.),
  fDisplacement(KThreeVector(0., 0., 0.))
{}
KSTrajTermMovingSurfaceUCN::KSTrajTermMovingSurfaceUCN(const KSTrajTermMovingSurfaceUCN& aCopy) :
  KSComponent(),
  fTheta(aCopy.fTheta),
  fPhi(aCopy.fPhi),
  fValueFormula(aCopy.fValueFormula),
  fValueMin(aCopy.fValueMin),
  fValueMax(aCopy.fValueMax),
  fDisplacement(aCopy.fDisplacement)
{}
KSTrajTermMovingSurfaceUCN* KSTrajTermMovingSurfaceUCN::Clone() const
{
    return new KSTrajTermMovingSurfaceUCN(*this);
}
KSTrajTermMovingSurfaceUCN::~KSTrajTermMovingSurfaceUCN() {}

void KSTrajTermMovingSurfaceUCN::Differentiate(double /*aTime*/, const KSTrajExactParticle& aParticle,
                                      KSTrajExactDerivative& aDerivative) const
{
    // Initialize the direction of the force normale to the surface
    KThreeVector tNormal(sin(fTheta) * cos(fPhi), sin(fTheta) * sin(fPhi), cos(fTheta));
    KThreeVector tForce = tNormal;

    // Calculate distance particle to surface
    double tTimeValue = aParticle.GetTime();
    double tParticleMass = aParticle.GetMass();

    KThreeVector tParticleCoordinates = aParticle.GetPosition() - fDisplacement;
    KThreeVector tInitialMomentum = aParticle.GetMomentum();

    double tDistanceParticleSurface = tParticleCoordinates.Dot(tForce) - fValueFunction->Eval(tTimeValue);

    // Estimate the space where the particle leave the moving part space
    double tControlTime = 1e-6;
    double tInitialNormalMomentumMagnitude = tInitialMomentum.Dot(tNormal);
    double tThicknessReflection = abs(tInitialNormalMomentumMagnitude/tParticleMass) * tControlTime;

    if (tDistanceParticleSurface <= 0) { // Act like a Heaviside function for the distance to the surface
      tForce.SetMagnitude(1e-22 + tParticleMass * fValueFunction->Derivative2(tTimeValue, 0, 0.001) );
    }
    else {
      tForce.SetMagnitude(0.);
    }

    if (0 <= tDistanceParticleSurface && tDistanceParticleSurface <= tThicknessReflection
          && tInitialNormalMomentumMagnitude >= 0) { // UCN reflection occured
      double fCorrelationLength = 20e-9;
      //double fAlpha = 5.e-6;
      //double fEta = 2.e-4;

      // Decompose the modified momentum of the particle
      KThreeVector tInitialNormalMomentum = -1*tInitialNormalMomentumMagnitude * tNormal;
      KThreeVector tInitialTangentMomentum = tInitialMomentum - tInitialNormalMomentum;
      KThreeVector tInitialOrthogonalMomentum = tInitialTangentMomentum.Cross(tInitialNormalMomentum.Unit());

      // Calculate the new reflection direction
      double k = tInitialMomentum.Magnitude() / katrin::KConst::Hbar();
      double cosThetaIn = tInitialNormalMomentum.Magnitude() / tInitialMomentum.Magnitude();
      double sinThetaIn = tInitialTangentMomentum.Magnitude() / tInitialMomentum.Magnitude();
      fTanThetaIn = sinThetaIn / cosThetaIn;
      double thetaIn = acos(cosThetaIn);
      fExpThetaCoef = (fCorrelationLength * k) * (fCorrelationLength * k) * cosThetaIn * cosThetaIn / 2;
      double expPhiCoef = (fCorrelationLength * k) * (fCorrelationLength * k) * sinThetaIn * sinThetaIn / 2;

      double phiOut = katrin::KRandom::GetInstance().Gauss(0., sqrt(0.5 / expPhiCoef));

      double deltaTheta = 0.;
      double tValueMin = ValueFunction(-thetaIn);
      double tValueMax = ValueFunction(katrin::KConst::Pi() / 2 - thetaIn);
      double tValue = katrin::KRandom::GetInstance().Uniform(tValueMin, tValueMax);

      fSolver.Solve(katrin::KMathBracketingSolver::eBrent,
                    this,
                    &KSTrajTermMovingSurfaceUCN::ValueFunction,
                    tValue,
                    -thetaIn,
                    katrin::KConst::Pi() / 2 - thetaIn,
                    deltaTheta);
      double thetaOut = thetaIn + deltaTheta;

      KThreeVector tFinalMomentum =
          -tInitialMomentum.Magnitude() * tInitialNormalMomentum.Unit() * cos(thetaOut) +
          tInitialMomentum.Magnitude() * tInitialTangentMomentum.Unit() * sin(thetaOut) * cos(phiOut) +
          tInitialMomentum.Magnitude() * tInitialOrthogonalMomentum.Unit() * sin(thetaOut) * sin(phiOut);

      KThreeVector tFinalVelocity = tFinalMomentum / tParticleMass;

      std::cout << tTimeValue << " "
                << tInitialMomentum << " "
                << tFinalMomentum << " "
                << std::endl;

      aDerivative.AddToVelocity(tFinalVelocity);
    }

    aDerivative.AddToForce(tForce);
}

void KSTrajTermMovingSurfaceUCN::Differentiate(double /*aTime*/, const KSTrajExactSpinParticle& aParticle,
                                      KSTrajExactSpinDerivative& aDerivative) const
{
  /* Working solution for simple reflection without taking account the UCN reflection effect
  */

  // Initialize the direction of the force normale to the surface
  KThreeVector tForce(sin(fTheta) * cos(fPhi), sin(fTheta) * sin(fPhi), cos(fTheta));

  // Calculate distance particle to surface
  double tTimeValue = aParticle.GetTime();
  KThreeVector tParticleCoordinates = aParticle.GetPosition() - fDisplacement;
  double tDistanceParticleSurface = tParticleCoordinates.Dot(tForce) - fValueFunction->Eval(tTimeValue);

  if (tDistanceParticleSurface <= 0) { // Act like a Heaviside function for the distance to the surface
    tForce.SetMagnitude(1e-22 + aParticle.GetMass() * fValueFunction->Derivative2(tTimeValue, 0, 0.001) );
  }
  else {
    tForce.SetMagnitude(0.);
  }

  aDerivative.AddToForce(tForce);
}

// void KSTrajTermMovingSurfaceUCN::Differentiate(double /*aTime*/, const KSTrajAdiabaticParticle& aParticle, KSTrajAdiabaticDerivative& aDerivative ) const
// {
//     aDerivative.AddToForce( fGravity );
// }

void KSTrajTermMovingSurfaceUCN::Differentiate(double /*aTime*/, const KSTrajAdiabaticSpinParticle& aParticle,
                                      KSTrajAdiabaticSpinDerivative& aDerivative) const
{
    // Initialize the direction of the force normale to the surface
    KThreeVector tForce(sin(fTheta) * cos(fPhi), sin(fTheta) * sin(fPhi), cos(fTheta));

    // Calculate distance particle to surface
    double tTimeValue = aParticle.GetTime();
    KThreeVector tParticleCoordinates = aParticle.GetPosition() - fDisplacement;
    double tDistanceParticleSurface = tParticleCoordinates.Dot(tForce) - fValueFunction->Eval(tTimeValue);

    if (tDistanceParticleSurface <= 0) { // Act like a Heaviside function for the distance to the surface
      double tForceMagnitude = aParticle.GetMass() * fValueFunction->Derivative2(tTimeValue, 0, 0.001);
      tForce.SetMagnitude(tForceMagnitude);
    }

    aDerivative.AddToForce(tForce);
}

// void KSTrajTermMovingSurfaceUCN::Differentiate(double /*aTime*/, const KSTrajElectricParticle& aParticle, KSTrajElectricDerivative& aDerivative ) const
// {
//     aDerivative.AddToForce( fGravity );
// }
//
// void KSTrajTermMovingSurfaceUCN::Differentiate(double /*aTime*/, const KSTrajMagneticParticle& aParticle, KSTrajMagneticDerivative& aDerivative ) const
// {
//     aDerivative.AddToForce( fGravity );
// }

void KSTrajTermMovingSurfaceUCN::SetTheta(const double& aTheta)
{
    fTheta = aTheta * katrin::KConst::Pi()/180;
    return;
}
void KSTrajTermMovingSurfaceUCN::SetPhi(const double& aPhi)
{
    fPhi = aPhi * katrin::KConst::Pi()/180;
    return;
}
void KSTrajTermMovingSurfaceUCN::SetValueFormula(const std::string& aValueFormula)
{
    fValueFormula = aValueFormula;
    SetValueFuntion();
    return;
}
void KSTrajTermMovingSurfaceUCN::SetValueMin(const double& aValueMin)
{
    fValueMin = aValueMin;
    SetValueFuntion();
    return;
}
void KSTrajTermMovingSurfaceUCN::SetValueMax(const double& aValueMax)
{
    fValueMax = aValueMax;
    SetValueFuntion();
    return;
}
void KSTrajTermMovingSurfaceUCN::SetDisplacement(const KThreeVector& aDisplacement)
{
    fDisplacement = aDisplacement;
    return;
}

void KSTrajTermMovingSurfaceUCN::SetValueFuntion()
{
    fValueFunction = new TF1("function", fValueFormula.c_str(), fValueMin, fValueMax);
    return;
}

double KSTrajTermMovingSurfaceUCN::ValueFunction(const double& aValue) const
{
    return fTanThetaIn * exp(-fExpThetaCoef * aValue * aValue) / 2 / sqrt(katrin::KConst::Pi() * fExpThetaCoef) +
           (1 + erf(aValue * sqrt(fExpThetaCoef))) / 2;
}

}  // namespace Kassiopeia
