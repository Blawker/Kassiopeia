/*
 * KSRootSurfaceMotionBuilder.cxx
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#include "KSRootSurfaceMotionBuilder.h"

#include "KSRootBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSRootSurfaceMotionBuilder::~KComplexElement() {}

STATICINT sKSRootSurfaceMotion =
    KSRootBuilder::ComplexElement<KSRootSurfaceMotion>("ks_root_surface_motion");

STATICINT sKSRootSurfaceMotionStructure =
    KSRootSurfaceMotionBuilder::Attribute<string>("name") +
    KSRootSurfaceMotionBuilder::Attribute<string>("set_surface_motion");

}  // namespace katrin
