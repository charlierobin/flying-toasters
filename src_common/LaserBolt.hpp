#ifndef LaserBolt_hpp
#define LaserBolt_hpp

#include "Sprite.hpp"

class LaserBolt : public Sprite {
    
public:
    
    LaserBolt( map<string, vector<gl::Texture2dRef>> * textures, float x, float y, float z, Color colour, float scaling, float scalingAdjust ) : Sprite( "LaserBolt", textures, scaling )
    {
        this->z = z;
        
        float s = this->z > 0.4 ? this->z : 0.4;
        
        this->x = x - ( 0.28 * 256 * s * scaling );
        this->y = y + ( 0.09 * 256 * s * scaling );
        
        this->xSpeed = this->xSpeed * 11;
        this->ySpeed = this->ySpeed * 11;
        
        this->colour = colour;
        
        this->scaleAdjust = scalingAdjust;
    };
    
    LaserBolt( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "LaserBolt", textures, scaling )
    {
        this->xSpeed = this->xSpeed * 2.1;
        this->ySpeed = this->ySpeed * 2.1;
    };
    
    void draw( float scaling )
    {
        gl::ScopedBlendAdditive a;
        
        Sprite::draw( scaling * this->scaleAdjust, this->colour );
    };
    
private:
    
    Color colour;
    float scaleAdjust = 1;
    
};

#endif /* LaserBolt_hpp */
