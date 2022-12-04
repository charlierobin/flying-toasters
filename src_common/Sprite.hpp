#ifndef Sprite_hpp
#define Sprite_hpp

#include "cinder/Rand.h"

#include "cinder/app/AppScreenSaver.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Sprite
{
    
public:
    
    Sprite( string, map<string, vector<gl::Texture2dRef>> *, float );
    
    virtual void update( double, vector<Sprite *> *, vector<Sprite *> *, float );
    virtual void draw( float );
    virtual void draw( float, Color );
    virtual void resize( float );
    
    virtual void updateIndex();
    
    float x;
    float y;
    float z;
    
    float rotation = 0;
    vec2 size;
    
    float xSpeed;
    float ySpeed;
    
    map<string, vector<gl::Texture2dRef>> * textures;
    string texture;
    int index = 0;
};

#define RIGHT cinder::vec3( 1, 0, 0 )
#define UP cinder::vec3( 0, 1, 0 )

#endif /* Sprite_hpp */
