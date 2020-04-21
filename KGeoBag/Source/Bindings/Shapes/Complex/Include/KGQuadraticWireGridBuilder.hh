#ifndef KGQUADRATICWIREGRIDBUILDER_HH_
#define KGQUADRATICWIREGRIDBUILDER_HH_

#include "KComplexElement.hh"

#include "KGWrappedSurface.hh"
#include "KGWrappedSpace.hh"
#include "KGQuadraticWireGrid.hh"

using namespace KGeoBag;

namespace katrin
{
  typedef KComplexElement<KGQuadraticWireGrid> KGQuadraticWireGridBuilder;

  template<>
  inline bool KGQuadraticWireGridBuilder::AddAttribute(KContainer* anAttribute)
  {
    if (anAttribute->GetName() == "radius")
    {
      anAttribute->CopyTo(fObject, &KGQuadraticWireGrid::SetR);
      return true;
    }
    if (anAttribute->GetName() == "pitch")
    {
      anAttribute->CopyTo(fObject, &KGQuadraticWireGrid::SetPitch);
      return true;
    }
    if (anAttribute->GetName() == "diameter")
    {
      anAttribute->CopyTo(fObject, &KGQuadraticWireGrid::SetDiameter);
      return true;
    }
    if (anAttribute->GetName() == "mesh_count_per_pitch")
    {
      anAttribute->CopyTo(fObject, &KGQuadraticWireGrid::SetNDiscPerPitch);
      return true;
    }
    if (anAttribute->GetName() == "add_outer_circle")
    {
      anAttribute->CopyTo(fObject, &KGQuadraticWireGrid::SetOuterCircle);
      return true;
    }
    return false;
  }

  typedef KComplexElement<KGWrappedSurface<KGQuadraticWireGrid> > KGQuadraticWireGridSurfaceBuilder;

  template<>
  inline bool KGQuadraticWireGridSurfaceBuilder::AddAttribute(KContainer* anAttribute)
  {
    if (anAttribute->GetName() == "name")
    {
      anAttribute->CopyTo(fObject, &KGWrappedSurface< KGQuadraticWireGrid >::SetName);
      return true;
    }
    return false;
  }

  template<>
  inline bool KGQuadraticWireGridSurfaceBuilder::AddElement(KContainer* anElement)
  {
    if (anElement->GetName() == "quadratic_wire_grid")
    {
      KGQuadraticWireGrid* object = NULL;
      anElement->ReleaseTo(object);
      object->Initialize();
      std::shared_ptr< KGQuadraticWireGrid > smartPtr(object);
      fObject->SetObject(smartPtr);
      return true;
    }
    return false;
  }


  typedef KComplexElement<KGWrappedSpace<KGQuadraticWireGrid> > KGQuadraticWireGridSpaceBuilder;

  template<>
  inline bool KGQuadraticWireGridSpaceBuilder::AddAttribute(KContainer* anAttribute)
  {
    if (anAttribute->GetName() == "name")
    {
      anAttribute->CopyTo(fObject, &KGWrappedSpace< KGQuadraticWireGrid >::SetName);
      return true;
    }
    return false;
  }

  template<>
  inline bool KGQuadraticWireGridSpaceBuilder::AddElement(KContainer* anElement)
  {
    if (anElement->GetName() == "quadratic_wire_grid")
    {
      KGQuadraticWireGrid* object = NULL;
      anElement->ReleaseTo(object);
      object->Initialize();
      std::shared_ptr< KGQuadraticWireGrid > smartPtr(object);
      fObject->SetObject(smartPtr);
      return true;
    }
    return false;
  }

}

#endif