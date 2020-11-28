#include "BurntToast.hpp"

#include "PuffOfSmoke.hpp"

using namespace cinder;

BurntToast::BurntToast() : Item::Item( "toast-burnt.png" )
{
}

void BurntToast::update( double time, std::vector<Item *> * toRemove, std::vector<Item *> * toInsert )
{
    Item::update( time, toRemove, toInsert );
    
    if ( position_.z > 20 ) return;
    
    if ( randInt( 0, 100 ) > 90 )
    {
        toInsert->push_back( new PuffOfSmoke( position_ ) );
    }
}
