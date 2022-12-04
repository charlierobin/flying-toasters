#ifndef PoliceToaster_h
#define PoliceToaster_h

#include "Sprite.hpp"

class PoliceToaster : public Sprite {
    
public:
    
    PoliceToaster( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "PoliceToaster", textures, scaling )
    {
        this->xSpeed = this->xSpeed * 2;
        this->ySpeed = this->ySpeed * 2;
        
        this->index = randInt( 29 );
    };
    
    void updateIndex()
    {
        this->index++;
        
        if ( this->index > 29 ) this->index = 0;
    };
};

#endif /* PoliceToaster_h */
