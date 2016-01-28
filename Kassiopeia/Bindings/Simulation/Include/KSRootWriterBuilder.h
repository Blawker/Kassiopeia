#ifndef Kassiopeia_KSRootWriterBuilder_h_
#define Kassiopeia_KSRootWriterBuilder_h_

#include "KComplexElement.hh"
#include "KSRootWriter.h"
#include "KSToolbox.h"

using namespace Kassiopeia;
namespace katrin
{

    typedef KComplexElement< KSRootWriter > KSRootWriterBuilder;

    template< >
    inline bool KSRootWriterBuilder::AddAttribute( KContainer* aContainer )
    {
        if( aContainer->GetName() == "name" )
        {
            aContainer->CopyTo( fObject, &KNamed::SetName );
            return true;
        }
        if( aContainer->GetName() == "add_writer" )
        {
            fObject->AddWriter( KSToolbox::GetInstance()->GetObjectAs< KSWriter >( aContainer->AsReference< string >() ) );
            return true;
        }
        return false;
    }

}

#endif