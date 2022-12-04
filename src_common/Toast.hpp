#ifndef Toast_hpp
#define Toast_hpp

#include "Sprite.hpp"

class Toast : public Sprite {
    
public:
    
    Toast( map<string, vector<gl::Texture2dRef>> * textures, float scaling ) : Sprite( "Toast", textures, scaling ){};
};

#endif /* Toast_hpp */
