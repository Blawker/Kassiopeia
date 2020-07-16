#ifndef Kassiopeia_KSTrajTermMovingSurfaceUCN_h_
#define Kassiopeia_KSTrajTermMovingSurfaceUCN_h_

#include "KSComponentTemplate.h"
#include "KSTrajAdiabaticSpinTypes.h"
#include "KSTrajAdiabaticTypes.h"
#include "KSTrajElectricTypes.h"
#include "KSTrajExactSpinTypes.h"
#include "KSTrajExactTypes.h"
#include "KSTrajMagneticTypes.h"

#include "TF1.h"
#include "KMathBracketingSolver.h"

namespace Kassiopeia
{

class KSTrajTermMovingSurfaceUCN :
    public KSComponentTemplate<KSTrajTermMovingSurfaceUCN>,
    public KSTrajExactDifferentiator,
    public KSTrajExactSpinDifferentiator,
    // public KSTrajAdiabaticDifferentiator,
    public KSTrajAdiabaticSpinDifferentiator  //,
// public KSTrajElectricDifferentiator,
// public KSTrajMagneticDifferentiator
{
  public:
    KSTrajTermMovingSurfaceUCN();
    KSTrajTermMovingSurfaceUCN(const KSTrajTermMovingSurfaceUCN& aCopy);
    KSTrajTermMovingSurfaceUCN* Clone() const override;
    ~KSTrajTermMovingSurfaceUCN() override;

  public:
    void Differentiate(double /*aTime*/, const KSTrajExactParticle& aValue,
                       KSTrajExactDerivative& aDerivative) const override;
    void Differentiate(double /*aTime*/, const KSTrajExactSpinParticle& aValue,
                       KSTrajExactSpinDerivative& aDerivative) const override;
    // virtual void Differentiate(double /*aTime*/, const KSTrajAdiabaticParticle& aValue, KSTrajAdiabaticDerivative& aDerivative ) const;
    void Differentiate(double /*aTime*/, const KSTrajAdiabaticSpinParticle& aValue,
                       KSTrajAdiabaticSpinDerivative& aDerivative) const override;
    // virtual void Differentiate(double /*aTime*/, const KSTrajMagneticParticle& aValue, KSTrajMagneticDerivative& aDerivative ) const;
    // virtual void Differentiate(double /*aTime*/, const KSTrajElectricParticle& aValue, KSTrajElectricDerivative& aDerivative ) const;

  public:
    void SetTheta(const double& aTheta);
    void SetPhi(const double& aPhi);
    void SetValueFormula(const std::string& aValueFormula);
    void SetValueMin(const double& aValueMin);
    void SetValueMax(const double& aValueMax);
    void SetDisplacement(const KThreeVector& aDisplacement);
    void SetValueFuntion();

  private:
    double fTheta;
    double fPhi;
    std::string fValueFormula;
    double fValueMin;
    double fValueMax;
    KThreeVector fDisplacement;

  /*private:
    double fTanThetaIn;
    double fExpThetaCoef;*/

  protected:
    TF1* fValueFunction;

  protected:
    double ValueFunction(const double& aValue) const;
    katrin::KMathBracketingSolver fSolver;
};

}  // namespace Kassiopeia

#endif
