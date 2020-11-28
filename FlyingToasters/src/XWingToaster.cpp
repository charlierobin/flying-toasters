#include "XWingToaster.hpp"

#include "LaserBolt.hpp"

using namespace cinder;

XWingToaster::XWingToaster() : Item::Item( "x-toaster.png" )
{
}

void XWingToaster::update( double time, std::vector<Item *> * toRemove, std::vector<Item *> * toInsert )
{
    Item::update( time, toRemove, toInsert );
    
    if ( position_.z > 40 ) return;
    
    if ( ! firingBurst_ && randInt( 0, 100 ) > 98 )
    {
        firingBurst_ = true;
    
        burstCount_ = 0;
        
        burstLength_ = randInt( 3, 6 );
        
        lastShot_ = app::getElapsedSeconds();
    }
    
    if ( firingBurst_ )
    {
        double now = app::getElapsedSeconds();
        
        if ( ( now - lastShot_ ) > 0.3 )
        {
            if ( switch_ )
            {
                toInsert->push_back( new LaserBolt( vec3( position_.x - ( 0.47 * size_.x ), position_.y - ( 0.21 * size_.y ), position_.z ), vec3( 1, 0, 0 ) ) );
                toInsert->push_back( new LaserBolt( vec3( position_.x + ( 0.12 * size_.x ), position_.y + ( 0.29 * size_.y ), position_.z ), vec3( 1, 0, 0 ) ) );
            }
            else
            {
                toInsert->push_back( new LaserBolt( vec3( position_.x - ( 0.45 * size_.x ), position_.y + ( 0.04 * size_.y ), position_.z ), vec3( 1, 0, 0 ) ) );
                toInsert->push_back( new LaserBolt( vec3( position_.x + ( 0.11 * size_.x ), position_.y - ( 0.03 * size_.y ), position_.z ), vec3( 1, 0, 0 ) ) );
            }
            
            switch_ = ! switch_;
            
            lastShot_ = now;
            
            burstCount_++;
        }
        
        if ( burstCount_ > burstLength_ )
        {
            firingBurst_ = false;
        }
    }
}

