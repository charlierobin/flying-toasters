#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include "Item.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class FlyingToastersApp : public App {
    
  public:
    
	void setup() override;
	void update() override;
	void draw() override;
    void resize() override;
    
private:
    
    vector<Item *> items_;
    vector<Item *> toRemove_;
    vector<Item *> toInsert_;
    
    CameraOrtho camera_;
    
    gl::GlslProgRef shader_;
    
    Timer timer_;
    
    int total_ = 0;
    int active_ = 0;
    int removed_ = 0;
    
    float windowWidth_ = 0;
};

void FlyingToastersApp::setup()
{
    camera_ = CameraOrtho( 0, getWindowWidth(), getWindowHeight(), 0, 0, 0 );
    
    setFrameRate( 60 );
    
    gl::enableVerticalSync( true );
    
    shader_ = gl::context()->getStockShader( gl::ShaderDef().color().texture() );
    
    
    shader_->bind();
    
    gl::enableAlphaBlending( true );
    
    
    timer_.start();
}

void FlyingToastersApp::update()
{
    bool needsSort = false;
    
    if ( randInt( 0, 100 ) > 95 )
    {
        items_.push_back( Item::random() );
        
        total_++;
        active_++;
        
        needsSort = true;
    }

    double seconds = timer_.getSeconds();
    
    timer_.start();
    
    for ( auto item : items_ )
    {
        item->update( seconds, &toRemove_, &toInsert_ );
    }
    
    for ( auto item : toRemove_ )
    {
        items_.erase( std::remove( items_.begin(), items_.end(), item ), items_.end() );
        
        delete item;
        
        removed_++;
        
        active_--;
    }
    
    toRemove_.clear();
    
    for ( auto item : toInsert_ )
    {
        items_.push_back( item );
        
        total_++;
        active_++;
        
        needsSort = true;
    }
    
    toInsert_.clear();
    
    if ( needsSort ) std::stable_sort( items_.begin(), items_.end(), [] ( Item * lhs, Item * rhs ) { return lhs->z() > rhs->z(); } );
    
    getWindow()->setTitle( to_string( active_ ) + " active, " + to_string( removed_ ) + " removed (" + to_string( total_ ) + " total)" );
}

void FlyingToastersApp::resize()
{
    for ( auto item : items_ )
    {
        item->resize( windowWidth_);
    }
    
    windowWidth_ = getWindowWidth();
}

void FlyingToastersApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    
    for ( auto item : items_ )
    {
        item->draw();
    }
}

CINDER_APP( FlyingToastersApp, RendererGl )

