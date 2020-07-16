#include "KSTrajTermMovingSurfaceUCNBuilder.h"

#include "KSRootBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSTrajTermMovingSurfaceUCNBuilder::~KComplexElement() {}

STATICINT sKSTrajTermMovingSurfaceUCNStructure =
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<string>("name") +
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<double>("theta") +
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<double>("phi") +
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<string>("value_formula") +
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<double>("value_min") +
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<double>("value_max") +
    KSTrajTermMovingSurfaceUCNBuilder::Attribute<KThreeVector>("displacement");

STATICINT sToolboxKSTrajTermMovingSurfaceUCN = KSRootBuilder::ComplexElement<KSTrajTermMovingSurfaceUCN>("kstraj_term_moving_surface");

}  // namespace katrin
