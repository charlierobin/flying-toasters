#include "FlyingToaster.hpp"
#include "PoliceToaster.hpp"
#include "Toast.hpp"
#include "BurntToast.hpp"
#include "TieFighterToaster.hpp"
#include "XWingToaster.hpp"

using namespace cinder;
using namespace cinder::app;

std::map<std::string, cinder::gl::Texture2dRef> cache_;

Item::Item( std::string resourceName, float scale, vec3 position )
{
    texture_ = Item::load( resourceName );
    
    scale_ = scale;
    
    size_ = vec2( getWindowWidth() / scale_, getWindowWidth() / scale_ );
    
    position_ = position;
    
    if ( position.z < 0 )
    {
        float z = randFloat( 0, 90 );
        
        if ( randInt( 0, 100 ) > 50 )
        {
            // appears somewhere along the right edge
            
            position_ = vec3( getWindowWidth() + size_.x, randFloat( 0, getWindowHeight() ), z );
        }
        else
        {
            // appears somewhere along the top edge
            
            position_ = vec3( randFloat( 0, getWindowWidth() ), - size_.y, z );
        }
    }
    
    speedRandom_ = randFloat( 0.8, 1.1 );
    
    resize( -1 );
}

void Item::update( double time, std::vector<Item *> * toRemove, std::vector<Item *> * toInsert )
{
    position_ = vec3( position_.x + ( speed_.x * time ), position_.y + ( speed_.y * time ), position_.z );
    
    if ( position_.x < -size_.x || position_.y > getWindowHeight() + size_.y )
    {
        toRemove->push_back( this );
    }
}

float Item::z()
{
    return position_.z;
}

void Item::draw()
{
    float colourFromZ = fmax( 1.0 - ( position_.z / 100.0 ), 0.5 );
    
    gl::ScopedColor colour( colourFromZ, colourFromZ, colourFromZ, 1 );
    
    gl::ScopedTextureBind tex0( texture_ );
    
    gl::drawBillboard( vec3( position_.x, position_.y, 0 ), size_, rotation_, RIGHT, UP );
}

void Item::resize( float oldWindowWidth )
{
    float size = ( getWindowWidth() / scale_ ) * ( 1.0 - ( position_.z / 90.0 ) );
        
    size_ = vec2( size, size );
    
    // monitor 1920 x 1200
    
    float ratio = getWindowWidth() / 1920.0;
    
    speed_ = vec2( -120.0 * ratio * speedRandom_, 60.0 * ratio * speedRandom_ );
    
    // TODO slower further away, faster the closer they are?
    
    
    
    if ( oldWindowWidth < 0 ) return;
    
    
    float change = getWindowWidth() / oldWindowWidth;
    
    position_ = vec3( position_.x * change, position_.y * change, position_.z );
}

// static

Item * Item::random()
{
    int chance = randInt( 0, 100 );
    
//    if ( chance > 80 ) return new XWingToaster();
    
    if ( chance > 65 )
    {
        return new FlyingToaster();
    }
    else if ( chance > 50 )
    {
        return new PoliceToaster();
    }
    else if ( chance > 25 )
    {
        return new TieFighterToaster();
    }
    else if ( chance > 15 )
    {
        return new XWingToaster();
    }
    else if ( chance > 1 )
    {
        return new Toast();
    }
    
    return new BurntToast();
}

gl::Texture2dRef Item::load( std::string resourceName )
{
    gl::Texture2dRef texture;
    
    if ( cache_.count( resourceName ) > 0 )
    {
        texture = cache_[ resourceName ];
        
//        std::cout << resourceName + " cached" << std::endl;
    }
    else
    {
        auto img = loadImage( loadResource( resourceName ) );
    
        texture = gl::Texture2d::create( img );
        
        cache_[ resourceName ] = texture;
        
//        std::cout << resourceName + " loaded" << std::endl;
    }
    
    return texture;
}




