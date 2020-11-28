#include "PuffOfSmoke.hpp"

using namespace cinder;
using namespace cinder::app;

PuffOfSmoke::PuffOfSmoke( vec3 position ) : Item::Item( "smoke.png", 20.0, position + vec3( 0, 0, 0.1 ) )
{
}

void PuffOfSmoke::update( double time, std::vector<Item *> * toRemove, std::vector<Item *> * toInsert )
{
    rotation_ = rotation_ + ( M_PI / 180.0 );
    
    lifetime_++;
    
    if ( lifetime_ > 120 )
    {
        toRemove->push_back( this );
    }
}

void PuffOfSmoke::draw()
{
    float colourFromZ = fmax( 1.0 - ( position_.z / 100.0 ), 0.5 );
    
    gl::ScopedColor colour( colourFromZ, colourFromZ, colourFromZ, 1 );
    
    gl::ScopedBlendAdditive scope;
    
    gl::ScopedTextureBind tex0( texture_ );
    
    gl::drawBillboard( vec3( position_.x, position_.y, 0 ), size_, rotation_, RIGHT, UP );
}
