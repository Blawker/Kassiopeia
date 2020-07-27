/*
 * KSIntMovingSurfaceUCN.h
 *
 *  Created on: 24.06.2020
 *      Author: T. Guilbaud
 */

#ifndef Kassiopeia_KSIntMovingSurfaceUCN_h_
#define Kassiopeia_KSIntMovingSurfaceUCN_h_

#include "KField.h"
#include "KMathBracketingSolver.h"
#include "KSSurfaceInteraction.h"
#include "TF1.h"

using katrin::KMathBracketingSolver;

namespace Kassiopeia
{

class KSStep;

class KSIntMovingSurfaceUCN : public KSComponentTemplate<KSIntMovingSurfaceUCN, KSSurfaceInteraction>
{
  public:
    KSIntMovingSurfaceUCN();
    KSIntMovingSurfaceUCN(const KSIntMovingSurfaceUCN& aCopy);
    KSIntMovingSurfaceUCN* Clone() const override;
    ~KSIntMovingSurfaceUCN() override;

  public:
    void ExecuteInteraction(const KSParticle& anInitialParticle, KSParticle& aFinalParticle,
                            KSParticleQueue& aSecondaries) override;
    void ExecuteReflection(const KSParticle& anInitialParticle, KSParticle& aFinalParticle,
                           KSParticleQueue& aSecondaries);
    void ExecuteTransmission(const KSParticle& anInitialParticle, KSParticle& aFinalParticle,
                             KSParticleQueue& aSecondaries);

  public:
    K_SET_GET(double, Eta);    // eta value (related to reflection probability)
    K_SET_GET(double, Alpha);  // alpha value (probability of spin sign flipping, so 1/2 of spin flip probability)
    K_SET_GET(double, RealOpticalPotential); // Fermi potential
    K_SET_GET(double, CorrelationLength);  // of the roughness
    K_SET_GET(double, ValueMin);
    K_SET_GET(double, ValueMax);

  public:
    void SetTheta(const double& aTheta);
    void SetPhi(const double& aPhi);
    void SetValueFormula(const std::string& aValueFormula);

    const double& GetTheta() const;
    const double& GetPhi() const;
    const std::string& GetValueFormula() const;
    
  protected:
    double fTheta; // Latitude angle in spherical representation (°)
    double fPhi; // Longitude angle in spherical representation (°)
    std::string fValueFormula; // Position dependent of time (m)

  private:
    double fTanThetaIn;
    double fExpThetaCoef;

  protected:
    TF1* fValueFunction;

  protected:
    double ValueFunction(const double& aValue) const;
    KMathBracketingSolver fSolver;
};

}  // namespace Kassiopeia

#endif
