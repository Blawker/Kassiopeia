/*
 * KSMotionSurfaceTranslationBuilder.cxx
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#include "KSMotionSurfaceTranslationBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSMotionSurfaceTranslationBuilder::~KComplexElement() {}

STATICINT sKSMotionSurfaceTranslationStructure = KSMotionSurfaceTranslationBuilder::Attribute<string>("name") +
                                      KSMotionSurfaceTranslationBuilder::Attribute<string>("surfaces") +
                                      KSMotionSurfaceTranslationBuilder::Attribute<double>("theta") +
                                      KSMotionSurfaceTranslationBuilder::Attribute<double>("phi") +
                                      KSMotionSurfaceTranslationBuilder::Attribute<string>("value_formula") +
                                      KSMotionSurfaceTranslationBuilder::Attribute<double>("value_min") +
                                      KSMotionSurfaceTranslationBuilder::Attribute<double>("value_max");

STATICINT sKSMotionSurfaceTranslationElement = KSRootBuilder::ComplexElement<KSMotionSurfaceTranslation>("ksmotion_surface_translation");
}  // namespace katrin
