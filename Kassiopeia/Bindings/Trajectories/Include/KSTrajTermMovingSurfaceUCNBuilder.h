#ifndef Kassiopeia_KSTrajTermMovingSurfaceUCNBuilder_h_
#define Kassiopeia_KSTrajTermMovingSurfaceUCNBuilder_h_

#include "KComplexElement.hh"
#include "KSTrajTermMovingSurfaceUCN.h"

using namespace Kassiopeia;
namespace katrin
{

typedef KComplexElement<KSTrajTermMovingSurfaceUCN> KSTrajTermMovingSurfaceUCNBuilder;

template<> inline bool KSTrajTermMovingSurfaceUCNBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "name") {
        aContainer->CopyTo(fObject, &KNamed::SetName);
        return true;
    }
    if (aContainer->GetName() == "theta") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurfaceUCN::SetTheta);
        return true;
    }
    if (aContainer->GetName() == "phi") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurfaceUCN::SetPhi);
        return true;
    }
    if (aContainer->GetName() == "value_formula") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurfaceUCN::SetValueFormula);
        return true;
    }
    if (aContainer->GetName() == "value_min") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurfaceUCN::SetValueMin);
        return true;
    }
    if (aContainer->GetName() == "value_max") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurfaceUCN::SetValueMax);
        return true;
    }
    if (aContainer->GetName() == "displacement") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurfaceUCN::SetDisplacement);
        return true;
    }
    return false;
}

}  // namespace katrin
#endif
