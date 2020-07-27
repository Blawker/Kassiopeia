/*
 * KSRootSurfaceMotionBuilder.h
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#ifndef Kassiopeia_KSRootSurfaceMotionBuilder_h_
#define Kassiopeia_KSRootSurfaceMotionBuilder_h_

#include "KComplexElement.hh"
#include "KSRootSurfaceMotion.h"
#include "KToolbox.h"

using namespace Kassiopeia;
namespace katrin
{

typedef KComplexElement<KSRootSurfaceMotion> KSRootSurfaceMotionBuilder;

template<> inline bool KSRootSurfaceMotionBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "name") {
        aContainer->CopyTo(fObject, &KNamed::SetName);
        return true;
    }
    if (aContainer->GetName() == "set_surface_motion") {
        fObject->SetSurfaceMotion(
            KToolbox::GetInstance().Get<KSSurfaceMotion>(aContainer->AsReference<std::string>()));
        return true;
    }
    return false;
}

}  // namespace katrin
#endif
