/*
 * KSRootSurfaceMotion.h
 *
 *  Created on: 24.07.2020
 *      Author: T. Guilbaud
 */

#ifndef _Kassiopeia_KSRootSurfaceMotion_h_
#define _Kassiopeia_KSRootSurfaceMotion_h_

#include "KSList.h"
#include "KSStep.h"
#include "KSSpace.h"
#include "KSSurface.h"
#include "KSSurfaceMotion.h"

namespace Kassiopeia
{

class KSRootSurfaceMotion : public KSComponentTemplate<KSRootSurfaceMotion, KSSurfaceMotion>
{
  public:
    KSRootSurfaceMotion();
    KSRootSurfaceMotion(const KSRootSurfaceMotion& aCopy);
    KSRootSurfaceMotion* Clone() const override;
    ~KSRootSurfaceMotion() override;

    //**************
    //surface motion
    //**************

  protected:
    void ExecuteMotion(const double aTimeValue) override;

    //***********
    //composition
    //***********

  public:
    void SetSurfaceMotion(KSSurfaceMotion* anMotion);
    void ClearSurfaceMotion(KSSurfaceMotion* anMotion);

  private:
    KSSurfaceMotion* fSurfaceMotion;

    //******
    //action
    //******

  public:
    void SetStep(KSStep* anStep);

    void ExecuteMotion();

  private:
    KSStep* fStep;
    KSParticle* fParticle;
};

}  // namespace Kassiopeia

#endif
