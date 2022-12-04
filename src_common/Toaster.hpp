#ifndef Toaster_hpp
#define Toaster_hpp

#include "Sprite.hpp"

class Toaster : public Sprite
{

public:
    
    Toaster( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "Toaster", textures, scaling )
    {
        this->index = randInt( 63 );
    };
    
    void updateIndex()
    {
        this->index++;
        
        switch ( this->state )
        {
            case Flapping:
                
                if ( this->index > 63 )
                {
                    if ( randInt( 5 ) > 1 )
                    {
                        this->index = 0;
                    }
                    else
                    {
                        this->index = 64;
                        this->state = StartingToCoast;
                    }
                }
                
                break;
                
            case StartingToCoast:
                
                if ( this->index > 86 )
                {
                    this->state = Coasting;
                }
                
                break;
                
            case Coasting:
                
                if ( this->index > 110 )
                {
                    if ( randInt( 5 ) > 1 )
                    {
                        this->index = 86;
                    }
                    else
                    {
                        this->index = 111;
                        this->state = FinishingCoast;
                    }
                }
                
                break;
                
            case FinishingCoast:
                
                if ( this->index > 130 )
                {
                    this->index = 0;
                    this->state = Flapping;
                }
                
                break;
                
            default:
                
                break;
        }
    };
    
    typedef enum
    {
        Flapping,
        StartingToCoast,
        Coasting,
        FinishingCoast
    }
    States;
    
    States state = Flapping;
};

#endif /* Toaster_hpp */
