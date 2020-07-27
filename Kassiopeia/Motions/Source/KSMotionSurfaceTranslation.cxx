/*
 * KSMotionSurfaceTranslation.cxx
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#include "KSMotionSurfaceTranslation.h"

#include "KRandom.h"
using katrin::KRandom;

#include "KConst.h"

namespace Kassiopeia
{

KSMotionSurfaceTranslation::KSMotionSurfaceTranslation() :
    fTheta(0.),
    fPhi(0.),
    fValueFormula("x"),
    fValueFunction(nullptr),
    fValueMin(0.),
    fValueMax(0.)
{}
KSMotionSurfaceTranslation::KSMotionSurfaceTranslation(const KSMotionSurfaceTranslation& aCopy) :
    KSComponent(),
    fTheta(aCopy.fTheta),
    fPhi(aCopy.fPhi),
    fValueFormula(aCopy.fValueFormula),
    fValueFunction(nullptr),
    fSurfaces(aCopy.fSurfaces),
    fOriginSurfaces(aCopy.fOriginSurfaces),
    fValueMin(aCopy.fValueMin),
    fValueMax(aCopy.fValueMax)
{}
KSMotionSurfaceTranslation* KSMotionSurfaceTranslation::Clone() const
{
    return new KSMotionSurfaceTranslation(*this);
}
KSMotionSurfaceTranslation::~KSMotionSurfaceTranslation() {}

void KSMotionSurfaceTranslation::ExecuteMotion(const double aTimeValue)
{
    if (fValueMin <= aTimeValue && aTimeValue <= fValueMax) {
        // Transformation to place the surface to it's final position
        KGeoBag::KTransformation* tDisplacementTransformation = new KGeoBag::KTransformation();

        // Set the direction vector of the motion
        KThreeVector tNewDistanceVector(sin(fTheta) * cos(fPhi),
                                        sin(fTheta) * sin(fPhi),
                                        cos(fTheta));

        // Calculate the new distance of the surface
        double tDistance = fValueFunction->Eval(aTimeValue);
        tNewDistanceVector.SetMagnitude(tDistance);

        // Modify each surfaces with the new distance
        auto tOriginSurface = fOriginSurfaces.begin();
        KThreeVector tSurfaceCurrentOrigin;
        KThreeVector tDisplacementVector;
        for (auto tSurface = fSurfaces.begin(); tSurface != fSurfaces.end(); ++tSurface) {
            tSurfaceCurrentOrigin = (*tSurface)->GetOrigin();
            tDisplacementVector = tSurfaceCurrentOrigin;

            tDisplacementVector = tNewDistanceVector + tOriginSurface[0] -tSurfaceCurrentOrigin;

            tDisplacementTransformation->SetDisplacement(tDisplacementVector);

            (*tSurface)->Transform(tDisplacementTransformation);

            ++tOriginSurface;
        }
    }
    return;
}

void KSMotionSurfaceTranslation::AddSurface(KGeoBag::KGSurface* aSurface)
{
    fSurfaces.push_back(aSurface);
    fOriginSurfaces.push_back(aSurface->GetOrigin());
}

bool KSMotionSurfaceTranslation::RemoveSurface(KGeoBag::KGSurface* aSurface)
{
    for (auto s = fSurfaces.begin(); s != fSurfaces.end(); ++s) {
        if ((*s) == aSurface) {
            fSurfaces.erase(s);
            return true;
        }
    }
    return false;
}

void KSMotionSurfaceTranslation::SetTheta(const double& aTheta) {
    fTheta = aTheta*katrin::KConst::Pi()/180;
    return;
}

void KSMotionSurfaceTranslation::SetPhi(const double& aPhi) {
    fPhi = aPhi*katrin::KConst::Pi()/180;
    return;
}

void KSMotionSurfaceTranslation::SetValueFormula(const std::string& aValueFormula) {
    fValueFormula = aValueFormula;
    fValueFunction = new TF1("function", fValueFormula.c_str(), 0., 1.);
    return;
}

const double& KSMotionSurfaceTranslation::GetTheta() const {
    return fTheta;
}

const double& KSMotionSurfaceTranslation::GetPhi() const {
    return fPhi;
}

const std::string& KSMotionSurfaceTranslation::GetValueFormula() const {
    return fValueFormula;
}

}  // namespace Kassiopeia
