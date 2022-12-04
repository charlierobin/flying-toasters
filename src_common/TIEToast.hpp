#ifndef TIEToast_hpp
#define TIEToast_hpp

#include "Sprite.hpp"

#include "LaserBolt.hpp"

class TIEToast : public Sprite {
    
public:
    
    TIEToast( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "TIEToast", textures, scaling )
    {
        this->xSpeed = this->xSpeed * 1.8;
        this->ySpeed = this->ySpeed * 1.8;
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
                
                toInsert->push_back( new LaserBolt( this->textures, this->x - ( 0.05 * 256 * s * scaling ), this->y + ( 0.06 * 256 * s * scaling ), this->z + 0.001, Color( 0, 1, 0 ), scaling, 0.9 ) );

                toInsert->push_back( new LaserBolt( this->textures, this->x + ( 0.02 * 256 * s * scaling ), this->y + ( 0.09 * 256 * s * scaling ), this->z + 0.001, Color( 0, 1, 0 ), scaling, 1 ) );

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
    
    int burstCount = 0;
    int burstLength = 0;
    
    double lastShot = 0;
    
    bool firingBurst = false;
};

#endif /* TIEToast_hpp */
