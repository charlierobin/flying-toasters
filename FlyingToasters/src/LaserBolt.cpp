#include "LaserBolt.hpp"

using namespace cinder;
using namespace cinder::app;

LaserBolt::LaserBolt( vec3 position, vec3 colour ) : Item::Item( "laser-bolt.png", 20.0, position - vec3( 0, 0, 0.1 ) )
{
    colour_ = colour;
}

void LaserBolt::update( double time, std::vector<Item *> * toRemove, std::vector<Item *> * toInsert )
{
    if ( bodge )
    {
        bodge = false;
        
        position_ = vec3( position_.x - ( size_.x * 0.3 ), position_.y + ( size_.y * 0.1 ), position_.z );
        
        speedRandom_ = 1;
        
        resize(-1);
        
        return;
    }
    
    position_ = vec3( position_.x + ( speedMultiplier_ * speed_.x * time ), position_.y + ( speedMultiplier_ * speed_.y * time ), position_.z );
    
    if ( position_.x < -size_.x || position_.y > getWindowHeight() + size_.y )
    {
        toRemove->push_back( this );
    }
}

void LaserBolt::draw()
{
    if ( bodge ) return;
    
    float colourFromZ = fmax( 1.0 - ( position_.z / 100.0 ), 0.5 );
    
    gl::ScopedColor colour( colour_.x, colour_.y, colour_.z, colourFromZ );
    
    gl::ScopedBlendAdditive scope;
    
    gl::ScopedTextureBind tex0( texture_ );
    
    gl::drawBillboard( vec3( position_.x, position_.y, 0 ), size_, rotation_, RIGHT, UP );
}
