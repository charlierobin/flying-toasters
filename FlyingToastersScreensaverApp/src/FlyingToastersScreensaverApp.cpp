#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "FlyingToasters.hpp"

class FlyingToastersScreensaverApp : public App
{
    
  public:
    
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    void resize() override;
    
private:
    
    FlyingToasters * flyingToasters;
    
};

void FlyingToastersScreensaverApp::setup()
{
    this->flyingToasters = new FlyingToasters();
    this->flyingToasters->setup();
}

void FlyingToastersScreensaverApp::resize()
{
    this->flyingToasters->resize();
}

void FlyingToastersScreensaverApp::mouseDown( MouseEvent event )
{
    this->flyingToasters->mouseDown( event );
}

void FlyingToastersScreensaverApp::update()
{
    this->flyingToasters->update();
}

void FlyingToastersScreensaverApp::draw()
{
    this->flyingToasters->draw();
}

CINDER_APP( FlyingToastersScreensaverApp, RendererGl )
