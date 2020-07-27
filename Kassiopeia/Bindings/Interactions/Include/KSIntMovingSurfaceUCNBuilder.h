/*
 * KSIntMovingSurfaceUCNBuilder.h
 *
 *  Created on: 24.06.2020
 *      Author: T. Guilbaud
 */

#ifndef Kassiopeia_KSIntMovingSurfaceUCNBuilder_h_
#define Kassiopeia_KSIntMovingSurfaceUCNBuilder_h_

#include "KComplexElement.hh"
#include "KSIntMovingSurfaceUCN.h"

using namespace Kassiopeia;
namespace katrin
{

typedef KComplexElement<KSIntMovingSurfaceUCN> KSIntMovingSurfaceUCNBuilder;

template<> inline bool KSIntMovingSurfaceUCNBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "name") {
        aContainer->CopyTo(fObject, &KNamed::SetName);
        return true;
    }
    if (aContainer->GetName() == "eta") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetEta);
        return true;
    }
    if (aContainer->GetName() == "alpha") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetAlpha);
        return true;
    }
    if (aContainer->GetName() == "real_optical_potential") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetRealOpticalPotential);
        return true;
    }
    if (aContainer->GetName() == "correlation_length") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetCorrelationLength);
        return true;
    }
    if (aContainer->GetName() == "theta") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetTheta);
        return true;
    }
    if (aContainer->GetName() == "phi") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetPhi);
        return true;
    }
    if (aContainer->GetName() == "value_formula") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetValueFormula);
        return true;
    }
    if (aContainer->GetName() == "value_min") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetValueMin);
        return true;
    }
    if (aContainer->GetName() == "value_max") {
        aContainer->CopyTo(fObject, &KSIntMovingSurfaceUCN::SetValueMax);
        return true;
    }
    return false;
}

}  // namespace katrin
#endif
