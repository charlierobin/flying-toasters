#ifndef ToastBurnt_hpp
#define ToastBurnt_hpp

#include "Sprite.hpp"

#include "Smoke.hpp"

class ToastBurnt : public Sprite {
    
public:
    
    ToastBurnt( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "ToastBurnt", textures, scaling )
    {
        this->xSpeed = this->xSpeed * 2;
        this->ySpeed = this->ySpeed * 2;
    };
    
    void update( double time, vector<Sprite *> * toRemove, vector<Sprite *> * toInsert, float scaling )
    {
        Sprite::update( time, toRemove, toInsert, scaling );
        
        if ( this->z < 0.4 ) return;
        
        if ( randInt( 0, 100 ) > 60 )
        {
            toInsert->push_back( new Smoke( this->textures, this->x, this->y, this->z + 0.001, scaling ) );
        }
    };
};

#endif /* ToastBurnt_hpp */
