/*
 * KSMotionSurfaceTranslation.h
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#ifndef Kassiopeia_KSMotionSurfaceTranslation_h_
#define Kassiopeia_KSMotionSurfaceTranslation_h_

#include "KField.h"
#include "KMathBracketingSolver.h"
#include "KSSurfaceMotion.h"
#include "TF1.h"

#include "KGCore.hh"
#include <vector>

using katrin::KMathBracketingSolver;

namespace Kassiopeia
{

class KSStep;

class KSMotionSurfaceTranslation : public KSComponentTemplate<KSMotionSurfaceTranslation, KSSurfaceMotion>
{
  public:
    KSMotionSurfaceTranslation();
    KSMotionSurfaceTranslation(const KSMotionSurfaceTranslation& aCopy);
    KSMotionSurfaceTranslation* Clone() const override;
    ~KSMotionSurfaceTranslation() override;

  public:
    void ExecuteMotion(const double aTimeValue) override;

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
    TF1* fValueFunction;

  private:
    std::vector<KGeoBag::KGSurface*> fSurfaces; // array of the surfaces to move
    std::vector<KThreeVector> fOriginSurfaces; // array of original poistion of the surfaces

  public:
    K_SET_GET(double, ValueMin);
    K_SET_GET(double, ValueMax);

  public:
    void AddSurface(KGeoBag::KGSurface* aSurface);
    bool RemoveSurface(KGeoBag::KGSurface* aSurface);
};

}  // namespace Kassiopeia

#endif
