#ifndef Smoke_hpp
#define Smoke_hpp

#include "Sprite.hpp"

class Smoke : public Sprite {
    
public:
    
    Smoke( map<string, vector<gl::Texture2dRef>> * textures, float x, float y, float z, float scaling ) : Sprite( "Smoke", textures, scaling )
    {
        this->x = x;
        this->y = y;
        this->z = z;
        
        this->xSpeed = this->xSpeed * 0.1;
        this->ySpeed = this->ySpeed * 0.1;
        
        this->rotationDirection = randFloat( 0.001, 0.01 );
        
        if ( randBool() ) this->rotationDirection = this->rotationDirection * -1;
        
        CueRef cue = timeline().add( bind( &Smoke::kill, this ), timeline().getCurrentTime() + 2 );
    };
    
    void updateIndex()
    {
        this->index++;
        
        if ( this->index > 31 ) this->index = 0;
    };
    
    void update( double time, vector<Sprite *> * toRemove, vector<Sprite *> * toInsert, float scaling )
    {
        Sprite::update( time, toRemove, toInsert, scaling );
    
        this->rotation = this->rotation + this->rotationDirection;
        
        switch ( this->state )
        {
            case Normal:
                
                this->scale = this->scale + 0.03;
                
                if ( this->scale > 1 ) this->scale = 1;
                
                this->colour = this->scale * 0.7;
                
                break;
                
            case Fading:
                
                this->colour = this->colour - 0.03;
                
                if ( this->colour < 0 )
                {
                    this->colour = 0;
                    
                    toRemove->push_back( this );
                }
                
                break;
                
            default:
                
                break;
        }
    };
    
    void draw( float scaling )
    {
        gl::ScopedBlendAdditive a;
        
        Sprite::draw( ( scaling / 2 ) * this->scale, Color( this->colour, this->colour, this->colour ) );
    };
    
    void kill()
    {
        this->state = Fading;
    };
    
private:
    
    float scale = 0;
    float rotationDirection = 0;
    float colour = 1;
    
    typedef enum
    {
        Normal,
        Fading
    }
    States;
    
    States state = Normal;
};

#endif /* Smoke_hpp */
