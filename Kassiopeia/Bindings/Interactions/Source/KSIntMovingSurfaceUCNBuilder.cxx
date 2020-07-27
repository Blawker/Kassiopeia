/*
 * KSIntMovingSurfaceUCNBuilder.cxx
 *
 *  Created on: 24.06.2020
 *      Author: T. Guilbaud
 */

#include "KSIntMovingSurfaceUCNBuilder.h"

#include "KSRootBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSIntMovingSurfaceUCNBuilder::~KComplexElement() {}

STATICINT sKSIntMovingSurfaceUCNStructure = KSIntMovingSurfaceUCNBuilder::Attribute<string>("name") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("eta") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("alpha") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("real_optical_potential") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("correlation_length") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("theta") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("phi") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<string>("value_formula") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("value_min") +
                                      KSIntMovingSurfaceUCNBuilder::Attribute<double>("value_max");

STATICINT sKSIntMovingSurfaceUCNElement = KSRootBuilder::ComplexElement<KSIntMovingSurfaceUCN>("ksint_moving_surface_UCN");
}  // namespace katrin
