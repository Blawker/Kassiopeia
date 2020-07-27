/*
 * KSMotionSurfaceTranslationBuilder.h
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#ifndef Kassiopeia_KSMotionSurfaceTranslationBuilder_h_
#define Kassiopeia_KSMotionSurfaceTranslationBuilder_h_

#include "KComplexElement.hh"
#include "KGCore.hh"
#include "KSMotionSurfaceTranslation.h"
#include "KSMotionsMessage.h"
#include "KSRootBuilder.h"

using namespace Kassiopeia;
namespace katrin
{

typedef KComplexElement<KSMotionSurfaceTranslation> KSMotionSurfaceTranslationBuilder;

template<> inline bool KSMotionSurfaceTranslationBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "name") {
        aContainer->CopyTo(fObject, &KNamed::SetName);
        return true;
    }
    if (aContainer->GetName() == "surfaces") {
        std::vector<KGeoBag::KGSurface*> tSurfaces =
            KGeoBag::KGInterface::GetInstance()->RetrieveSurfaces(aContainer->AsReference<std::string>());
        std::vector<KGeoBag::KGSurface*>::iterator tSurfaceIt;
        KGeoBag::KGSurface* tSurface;

        if (tSurfaces.size() == 0) {
            movmsg(eError) << "no surfaces found for specifier <" << aContainer->AsReference<std::string>() << ">"
                      << eom;
            return true;
        }

        for (tSurfaceIt = tSurfaces.begin(); tSurfaceIt != tSurfaces.end(); tSurfaceIt++) {
            tSurface = *tSurfaceIt;
            fObject->AddSurface(tSurface);
        }
        return true;
    }
    if (aContainer->GetName() == "theta") {
        aContainer->CopyTo(fObject, &KSMotionSurfaceTranslation::SetTheta);
        return true;
    }
    if (aContainer->GetName() == "phi") {
        aContainer->CopyTo(fObject, &KSMotionSurfaceTranslation::SetPhi);
        return true;
    }
    if (aContainer->GetName() == "value_formula") {
        aContainer->CopyTo(fObject, &KSMotionSurfaceTranslation::SetValueFormula);
        return true;
    }
    if (aContainer->GetName() == "value_min") {
        aContainer->CopyTo(fObject, &KSMotionSurfaceTranslation::SetValueMin);
        return true;
    }
    if (aContainer->GetName() == "value_max") {
        aContainer->CopyTo(fObject, &KSMotionSurfaceTranslation::SetValueMax);
        return true;
    }
    return false;
}

}  // namespace katrin
#endif
