#include "TieFighterToaster.hpp"

#include "LaserBolt.hpp"

using namespace cinder;

TieFighterToaster::TieFighterToaster() : Item::Item( "TIE-toaster.png" )
{
}

void TieFighterToaster::update( double time, std::vector<Item *> * toRemove, std::vector<Item *> * toInsert )
{
    Item::update( time, toRemove, toInsert );
    
    if ( position_.z > 20 ) return;
    
    if ( ! firingBurst_ && randInt( 0, 100 ) > 98 )
    {
        firingBurst_ = true;
        
        burstCount_ = 0;
        
        burstLength_ = randInt( 2, 5 );
        
        lastShot_ = app::getElapsedSeconds();
    }
    
    if ( firingBurst_ )
    {
        double now = app::getElapsedSeconds();
        
        if ( ( now - lastShot_ ) > 0.15 )
        {
            toInsert->push_back( new LaserBolt( vec3( position_.x - ( 0.16 * size_.x ), position_.y + ( 0.06 * size_.y ), position_.z ), vec3( 0, 1, 0 ) ) );
            toInsert->push_back( new LaserBolt( vec3( position_.x - ( 0.06 * size_.x ), position_.y + ( 0.11 * size_.y ), position_.z ), vec3( 0, 1, 0 ) ) );
            
            lastShot_ = now;
            
            burstCount_++;
        }
        
        if ( burstCount_ > burstLength_ )
        {
            firingBurst_ = false;
        }
    }
}
