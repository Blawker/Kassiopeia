/*
 * KSRootSurfaceMotion.cxx
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#include "KSRootSurfaceMotion.h"

#include "KRandom.h"
#include "KSException.h"
#include "KSMotionsMessage.h"
using katrin::KRandom;

namespace Kassiopeia
{

KSRootSurfaceMotion::KSRootSurfaceMotion() :
    fStep(nullptr),
    fParticle(nullptr)
{}
KSRootSurfaceMotion::KSRootSurfaceMotion(const KSRootSurfaceMotion& aCopy) :
    KSComponent(),
    fStep(aCopy.fStep),
    fParticle(aCopy.fParticle)
{}
KSRootSurfaceMotion* KSRootSurfaceMotion::Clone() const
{
    return new KSRootSurfaceMotion(*this);
}
KSRootSurfaceMotion::~KSRootSurfaceMotion() {}

void KSRootSurfaceMotion::ExecuteMotion(const double aTimeValue)
{
    for (int tIndex = 0; tIndex < fSurfaceMotions.End(); tIndex++) {
        try {
            fSurfaceMotions.ElementAt(tIndex)->ExecuteMotion(aTimeValue);
        }
        catch (KSException const& e) {
            throw KSMotionError().Nest(e)
                << "Failed to execute surface motion <" << fSurfaceMotions.ElementAt(tIndex)->GetName() << ">.";
        }
    }
    return;
}

void KSRootSurfaceMotion::AddSurfaceMotion(KSSurfaceMotion* anSurfaceMotion)
{
    fSurfaceMotions.AddElement(anSurfaceMotion);
    return;
}
void KSRootSurfaceMotion::RemoveSurfaceMotion(KSSurfaceMotion* anSurfaceMotion)
{
    fSurfaceMotions.RemoveElement(anSurfaceMotion);
    return;
}

void KSRootSurfaceMotion::SetStep(KSStep* aStep)
{
    fStep = aStep;
    fParticle = &(aStep->InitialParticle());
    return;
}

void KSRootSurfaceMotion::PushUpdateComponent()
{
    for (int tIndex = 0; tIndex < fSurfaceMotions.End(); tIndex++) {
        fSurfaceMotions.ElementAt(tIndex)->PushUpdate();
    }
}

void KSRootSurfaceMotion::PushDeupdateComponent()
{
    for (int tIndex = 0; tIndex < fSurfaceMotions.End(); tIndex++) {
        fSurfaceMotions.ElementAt(tIndex)->PushDeupdate();
    }
}

void KSRootSurfaceMotion::ExecuteMotion()
{
    const double tTimeValue = fParticle->GetTime();
    ExecuteMotion(tTimeValue);

    return;
}

STATICINT sKSRootSurfaceMotionDict = KSDictionary<KSRootSurfaceMotion>::AddCommand(
    &KSRootSurfaceMotion::AddSurfaceMotion, &KSRootSurfaceMotion::RemoveSurfaceMotion,
    "add_surface_motion", "remove_surface_motion");

}  // namespace Kassiopeia
