#ifndef FlyingToasters_hpp
#define FlyingToasters_hpp

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"

#include "Sprites.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

struct TexturePreload
{
    string filename;
    string loadInto;
};

class FlyingToasters
{
    
public:
    
    FlyingToasters();
    
    void setup();
    void resize();
    void mouseDown( MouseEvent event ){};
    void update();
    void draw();
    
private:
    
    void sampleFPS();
    void createNewSprite();
    
    CameraOrtho camera;
    
    gl::GlslProgRef shader;
    
    vector<Sprite *> sprites;
    vector<Sprite *> toRemove;
    vector<Sprite *> toInsert;
    
    Timer timer;
    
    int counter = 0;
    int fps = 0;
    
    int total = 0;
    int active = 0;
    int removed = 0;
    
    float scaling;
    
    bool create = false;
    
    float previousWindowWidth;
    
    map<string, vector<gl::Texture2dRef>> textures;
    
    vector<TexturePreload> toPreload;
    
    void addToPreload( string, string );
    void addSequenceToPreload( string, int, string );
};

#endif /* FlyingToasters_hpp */
