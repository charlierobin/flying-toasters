#include "cinder/app/AppScreenSaver.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Log.h"

#include "FlyingToasters.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class FlyingToastersScreensaver : public AppScreenSaver
{
    
  public:
    
	void setup() override;
	void update() override;
	void draw() override;
	
private:
    
    vector<FlyingToasters *> flyingToasters;
    map<gl::Context *, FlyingToasters *> contexts;
};

void FlyingToastersScreensaver::setup()
{
    // https://libcinder.org/docs/guides/logging/index.html
    
//    log::makeLogger<log::LoggerFile>( "/Users/charlie/Desktop/FlyingToasters.log" );
}

void FlyingToastersScreensaver::update()
{
//    CI_LOG_D( gl::Context::getCurrent() );
    
    for ( auto const& f : this->flyingToasters )
    {
        f->update();
    }
}

void FlyingToastersScreensaver::draw()
{
    gl::Context * c = gl::Context::getCurrent();
    
//    CI_LOG_D( c );
    
    FlyingToasters * f = this->contexts[ c ];
    
    if ( f )
    {
        f->draw();
    }
    else
    {
        FlyingToasters * n = new FlyingToasters();
        n->setup();
        
        this->flyingToasters.push_back( n );
        
        this->contexts[ c ] = n;
        
        n->draw();
    }
    
    // https://github.com/cinder/Cinder/blob/master/include/cinder/gl/Context.h
}

CINDER_APP_SCREENSAVER( FlyingToastersScreensaver, RendererGl, [&]( AppScreenSaver::Settings *settings )
{
//    https://github.com/cinder/Cinder/blob/master/test/ScreenSaverTest/src/ScreenSaverTestApp.cpp
//    https://github.com/cinder/Cinder/blob/master/include/cinder/app/AppScreenSaver.h
    
//    settings->setHighDensityDisplayEnabled();

//    settings->enableSecondaryDisplayBlanking( true );
    
//    settings->disableFrameRate();
    
//    settings->enableDebug();
} )

