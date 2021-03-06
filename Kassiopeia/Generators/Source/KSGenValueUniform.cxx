#include "KSGenValueUniform.h"

#include "KRandom.h"
using katrin::KRandom;

namespace Kassiopeia
{

KSGenValueUniform::KSGenValueUniform() : fValueMin(0.), fValueMax(0.) {}
KSGenValueUniform::KSGenValueUniform(const KSGenValueUniform& aCopy) :
    KSComponent(),
    fValueMin(aCopy.fValueMin),
    fValueMax(aCopy.fValueMax)
{}
KSGenValueUniform* KSGenValueUniform::Clone() const
{
    return new KSGenValueUniform(*this);
}
KSGenValueUniform::~KSGenValueUniform() {}

void KSGenValueUniform::DiceValue(vector<double>& aDicedValues)
{
    double tValue = KRandom::GetInstance().Uniform(fValueMin, fValueMax);
    aDicedValues.push_back(tValue);
    return;
}

}  // namespace Kassiopeia
