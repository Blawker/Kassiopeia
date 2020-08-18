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
    void AddSurfaceMotion(KSSurfaceMotion* anMotion);
    void RemoveSurfaceMotion(KSSurfaceMotion* anMotion);

  private:
    KSList<KSSurfaceMotion> fSurfaceMotions;

    //******
    //action
    //******

  public:
    void SetStep(KSStep* anStep);

    void ExecuteMotion();

    void PushUpdateComponent() override;
    void PushDeupdateComponent() override;

  private:
    KSStep* fStep;
    KSParticle* fParticle;
};

}  // namespace Kassiopeia

#endif
