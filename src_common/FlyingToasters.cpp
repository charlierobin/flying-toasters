#include "FlyingToasters.hpp"

FlyingToasters::FlyingToasters(){}

void FlyingToasters::setup()
{
    Rand::randomize();
    
    this->addToPreload( "spot.png", "Spot" );
    
    this->addToPreload( "laser-bolt.png", "LaserBolt" );
    this->addToPreload( "TIE-fighter.png", "TIEToast" );
    this->addToPreload( "toast-burnt.png", "ToastBurnt" );
    this->addToPreload( "toast.png", "Toast" );
    this->addToPreload( "X-wing.png", "XWingToast" );
    
    this->addSequenceToPreload( "police_%04d.png", 29,"PoliceToaster" );
    this->addSequenceToPreload( "smoke_%04d.png", 31,"Smoke" );
    this->addSequenceToPreload( "toaster_%04d.png", 130,"Toaster" );
    
    setFrameRate( 30 );
    
    this->camera = CameraOrtho( 0, getWindowWidth(), getWindowHeight(), 0, 0, 0 );

    this->shader = gl::context()->getStockShader( gl::ShaderDef().color().texture() );
    
    this->shader->bind();
    
    gl::enableAlphaBlending( true );
    
    this->timer.start();
    
    CueRef cue = timeline().add( bind( &FlyingToasters::sampleFPS, this ), timeline().getCurrentTime() + 5 );
    
    this->scaling = getWindowWidth() / 2560.0;
}

void FlyingToasters::addToPreload( string filename, string targetGroup )
{
    TexturePreload toPreload;
    
    toPreload.filename = filename;
    toPreload.loadInto = targetGroup;
    
    this->toPreload.push_back( toPreload );
}

void FlyingToasters::addSequenceToPreload( string filename, int count, string targetGroup )
{
    char buffer [50];
    
    for ( int i = 0; i <= count; i++ )
    {
        sprintf ( buffer, filename.c_str(), i );
        this->addToPreload( buffer, targetGroup );
    }
}

void FlyingToasters::resize()
{
    this->scaling = getWindowWidth() / 2560.0;
    
    float delta = getWindowWidth() / this->previousWindowWidth;
    
    for ( auto sprite : this->sprites )
    {
        sprite->resize( delta );
    }
    
    this->previousWindowWidth = getWindowWidth();
}

void FlyingToasters::sampleFPS()
{
    this->fps = this->counter / 5;
    
    this->counter = 0;
    
    CueRef cue = timeline().add( bind( &FlyingToasters::sampleFPS, this ), timeline().getCurrentTime() + 5 );
}

void FlyingToasters::createNewSprite()
{
    CueRef cue = timeline().add( bind( &FlyingToasters::createNewSprite, this ), timeline().getCurrentTime() + randFloat( 0.5, 1 ) );
    
    this->create = true;
}

void FlyingToasters::update()
{
    if ( this->toPreload.size() > 0 )
    {
        TexturePreload item = this->toPreload.front();
        
        auto img = loadImage( app::loadResource( item.filename ) );
        
        if ( this->textures.find( item.loadInto ) == this->textures.end() )
        {
            this->textures[ item.loadInto ] = *new vector<gl::Texture2dRef>;
        }
        
        this->textures[ item.loadInto ].push_back( gl::Texture2d::create( img ) );
        
        this->toPreload.erase( this->toPreload.begin() );
        
        if ( this->toPreload.size() == 0 )
        {
            CueRef cue = timeline().add( bind( &FlyingToasters::createNewSprite, this ), timeline().getCurrentTime() + randFloat( 0.1, 0.5 ) );
        }
        
        getWindow()->setTitle( to_string( this->toPreload.size() ) + " preloaded" );
        
        return;
    }
    
    bool needsSort = false;
    
    if ( this->create )
    {
        this->create = false;
        
        this->sprites.push_back( Sprites::getNewRandom( &this->textures, this->scaling ) );
        
        this->total++;
        this->active++;
        
        needsSort = true;
    }
    
    double seconds = this->timer.getSeconds();
    
    this->timer.start();
    
    // TODO ref, pointer ?
    
    for ( auto const& sprite : this->sprites )
    {
        sprite->update( seconds, &this->toRemove, &this->toInsert, this->scaling );
    }
    
    for ( auto const& sprite : this->toRemove )
    {
        
        // TODO
        
        this->sprites.erase( remove( this->sprites.begin(), this->sprites.end(), sprite ), this->sprites.end() );
        
        delete sprite;
        
        
        
        this->removed++;
        
        this->active--;
    }
    
    this->toRemove.clear();
    
    for ( auto const& sprite : this->toInsert )
    {
        this->sprites.push_back( sprite );
        
        this->total++;
        this->active++;
        
        needsSort = true;
    }
    
    this->toInsert.clear();
    
    if ( needsSort ) std::stable_sort( this->sprites.begin(), this->sprites.end(), [] ( Sprite * lhs, Sprite * rhs )
    {
        return lhs->z < rhs->z;
    } );
    
    this->counter++;
    
    getWindow()->setTitle( to_string( this->active ) + " active, " + to_string( this->removed ) + " removed (" + to_string( this->total ) + " total), fps: " + to_string( this->fps ) );
}

void FlyingToasters::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    
    for ( auto const& sprite : this->sprites )
    {
        sprite->draw( this->scaling );
    }
}
