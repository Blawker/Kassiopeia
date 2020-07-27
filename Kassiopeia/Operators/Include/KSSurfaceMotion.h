/*
 * KSSurfaceMotion.h
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#ifndef Kassiopeia_KSSurfaceMotion_h_
#define Kassiopeia_KSSurfaceMotion_h_

#include "KSComponentTemplate.h"
#include "KSParticle.h"

namespace Kassiopeia
{

class KSSurfaceMotion : public KSComponentTemplate<KSSurfaceMotion>
{
  public:
    KSSurfaceMotion();
    ~KSSurfaceMotion() override;

  public:
    virtual void ExecuteMotion(const double aTimeValue) = 0;
};

}  // namespace Kassiopeia

#endif
