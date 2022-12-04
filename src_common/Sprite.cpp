#include "Sprite.hpp"

Sprite::Sprite( string name, map<string, vector<gl::Texture2dRef>> * textures, float scaling )
{
    this->textures = textures;
    this->texture = name;
    
    this->size = vec2( 256, 256 );
    
    if ( randInt( getWindowWidth() + getWindowHeight() ) > getWindowWidth() )
    {
        this->x = getWindowWidth() + ( this->size.x * scaling );
        this->y = randFloat( 0, getWindowHeight() - ( this->size.y * scaling ) );
    }
    else
    {
        this->x = randFloat( this->size.x * scaling, getWindowWidth() );
        this->y = - this->size.y * scaling;
    }
    
    this->z = randFloat();
    
    this->xSpeed = -180;
    this->ySpeed = 90;
}

void Sprite::updateIndex()
{
}

void Sprite::update( double time, vector<Sprite *> * toRemove, vector<Sprite *> * toInsert, float scaling )
{
    this->updateIndex();
    
    float s = this->z > 0.4 ? this->z : 0.4;
    
    this->x = this->x + ( ( this->xSpeed * time ) * scaling * s );
    this->y = this->y + ( ( this->ySpeed * time ) * scaling * s );
    
    if ( this->x < - this->size.x || this->y > getWindowHeight() + this->size.y )
    {
        toRemove->push_back( this );
    }
}

void Sprite::draw( float scaling )
{
    float s = this->z > 0.4 ? this->z : 0.4;
    
    gl::ScopedColor colour( s, s, s, 1 );
    
    map<string, vector<gl::Texture2dRef>>::iterator it = this->textures->find( this->texture );
    
    if ( it == this->textures->end() )
    {
        it = this->textures->find( "Spot" );
    }
    
    vector<gl::Texture2dRef> t = it->second;

    gl::ScopedTextureBind tex0( t[ this->index ] );
    
    gl::drawBillboard( vec3( this->x, this->y, 0 ), this->size * scaling * s, this->rotation, RIGHT, UP );
}

void Sprite::draw( float scaling, Color c )
{
    float s = this->z > 0.4 ? this->z : 0.4;
    
    gl::ScopedColor colour( c.r, c.g, c.b, s );
    
    map<string, vector<gl::Texture2dRef>>::iterator it = this->textures->find( this->texture );
    
    if ( it == this->textures->end() )
    {
        it = this->textures->find( "Spot" );
    }
    
    vector<gl::Texture2dRef> t = it->second;

    gl::ScopedTextureBind tex0( t[ this->index ] );
    
    gl::drawBillboard( vec3( this->x, this->y, 0 ), this->size * scaling * s, this->rotation, RIGHT, UP );
}

void Sprite::resize( float delta )
{
    this->x = this->x * delta;
    this->y = this->y * delta;
}
