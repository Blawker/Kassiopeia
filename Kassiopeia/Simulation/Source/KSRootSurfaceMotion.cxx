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
    //fSurfaceMotion(nullptr),
    fStep(nullptr),
    fParticle(nullptr)
{}
KSRootSurfaceMotion::KSRootSurfaceMotion(const KSRootSurfaceMotion& aCopy) :
    KSComponent(),
    //fSurfaceMotion(aCopy.fSurfaceMotion),
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
    /*if (fSurfaceMotion == nullptr) {
        movmsg(eError) << "<" << GetName() << "> cannot execute motion with no surface motion set" << eom;
    }*/

    for (int tIndex = 0; tIndex < fSurfaceMotions.End(); tIndex++) {
        try {
            fSurfaceMotions.ElementAt(tIndex)->ExecuteMotion(aTimeValue);
            //fSurfaceMotion->ExecuteMotion(aTimeValue);
        }
        catch (KSException const& e) {
            throw KSMotionError().Nest(e)
                << "Failed to execute surface motion <" << fSurfaceMotions.ElementAt(tIndex)->GetName() << ">.";
        }
    }
    return;
}

/*void KSRootSurfaceMotion::SetSurfaceMotion(KSSurfaceMotion* aSurfaceMotion)
{
    if (fSurfaceMotion != nullptr) {
        movmsg(eError) << "<" << GetName() << "> tried to set surface motion <" << aSurfaceMotion->GetName()
                       << "> with surface motion <" << fSurfaceMotion->GetName() << "> already set" << eom;
        return;
    }
    movmsg_debug("<" << GetName() << "> setting surface motion <" << aSurfaceMotion->GetName() << ">" << eom);
    fSurfaceMotion = aSurfaceMotion;
    return;
}
void KSRootSurfaceMotion::ClearSurfaceMotion(KSSurfaceMotion* aSurfaceMotion)
{
    if (fSurfaceMotion != aSurfaceMotion) {
        movmsg(eError) << "<" << GetName() << "> tried to remove surface motion <"
                       << aSurfaceMotion->GetName() << "> with surface motion <"
                       << fSurfaceMotion->GetName() << "> already set" << eom;
        return;
    }
    movmsg_debug("<" << GetName() << "> clearing surface motion <" << aSurfaceMotion->GetName() << ">"
                     << eom);
    fSurfaceMotion = nullptr;
    return;
}*/

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
    /*if (fSurfaceMotion == nullptr) {
        return;
    }*/

    const double tTimeValue = fParticle->GetTime();
    ExecuteMotion(tTimeValue);

    return;
}

STATICINT sKSRootSurfaceMotionDict = KSDictionary<KSRootSurfaceMotion>::AddCommand(
    &KSRootSurfaceMotion::AddSurfaceMotion, &KSRootSurfaceMotion::RemoveSurfaceMotion,
    "add_surface_motion", "remove_surface_motion");

}  // namespace Kassiopeia
