#ifndef Item_hpp
#define Item_hpp

#include "cinder/Rand.h"

class Item {
    
public:
    
    static Item * random();
    static cinder::gl::Texture2dRef load( std::string );
    
    Item( std::string name ) : Item( name, 8.0, cinder::vec3( 0, 0, -1 ) ){};
    Item( std::string, float, cinder::vec3 );
    
    virtual void update( double, std::vector<Item *> *, std::vector<Item *> * );
    virtual void draw();
    
    void resize( float );
    
    float z();
    
protected:
    
    cinder::vec3 position_;
    cinder::vec2 speed_;
    
    float speedRandom_;
    
    float rotation_ = 0.0f;
    
    float scale_;
    cinder::vec2 size_;
    
//private:
    
    cinder::gl::Texture2dRef texture_;
};

#define RIGHT cinder::vec3( 1, 0, 0 )
#define UP cinder::vec3( 0, 1, 0 )

#endif /* Item_hpp */
