#ifndef XWingToast_hpp
#define XWingToast_hpp

#include "Sprite.hpp"

#include "LaserBolt.hpp"

class XWingToast : public Sprite {
    
public:
    
    XWingToast( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "XWingToast", textures, scaling )
    {
        this->xSpeed = this->xSpeed * 2.1;
        this->ySpeed = this->ySpeed * 2.1;
    };
    
    void update( double time, vector<Sprite *> * toRemove, vector<Sprite *> * toInsert, float scaling )
    {
        Sprite::update( time, toRemove, toInsert, scaling );
        
        if ( this->z < 0.4 ) return;
        
        if ( ! this->firingBurst && randInt( 0, 100 ) > 98 )
        {
            this->firingBurst = true;

            this->burstCount = 0;
            
            this->burstLength = randInt( 1, 3 );
            
            this->lastShot = app::getElapsedSeconds();
        }

        if ( this->firingBurst )
        {
            double now = app::getElapsedSeconds();
            
            if ( ( now - this->lastShot ) > 0.2 )
            {
                float s = this->z > 0.4 ? this->z : 0.4;
                
                if ( this->switchSide )
                {
                    toInsert->push_back( new LaserBolt( this->textures, this->x - ( 0.49 * 256 * s * scaling ), this->y - ( 0.16 * 256 * s * scaling ), this->z + 0.001, Color( 1, 0, 0 ), scaling, 0.7 ) );
                    toInsert->push_back( new LaserBolt( this->textures, this->x + ( 0.11 * 256 * s * scaling ), this->y + ( 0.37 * 256 * s * scaling ), this->z + 0.001, Color( 1, 0, 0 ), scaling, 1 ) );
                }
                else
                {
                    toInsert->push_back( new LaserBolt( this->textures, this->x - ( 0.47 * 256 * s * scaling ), this->y + ( 0.09 * 256 * s * scaling ), this->z + 0.001, Color( 1, 0, 0 ), scaling, 0.7 ) );
                    toInsert->push_back( new LaserBolt( this->textures, this->x + ( 0.11 * 256 * s * scaling ), this->y + ( 0.06 * 256 * s * scaling ), this->z + 0.001, Color( 1, 0, 0 ), scaling, 1 ) );
                }
                
                this->switchSide = ! this->switchSide;
                
                this->lastShot = now;
                
                this->burstCount++;
            }
            
            if ( this->burstCount > this->burstLength )
            {
                this->firingBurst = false;
            }
        }

    };
    
private:
    
    bool switchSide = false;
    
    int burstCount = 0;
    int burstLength = 0;
    
    double lastShot = 0;
    
    bool firingBurst = false;
};

#endif /* XWingToast_hpp */
