#ifndef Sprites_hpp
#define Sprites_hpp

#include "cinder/Rand.h"

#include "Toaster.hpp"
#include "Toast.hpp"
#include "ToastBurnt.hpp"
#include "PoliceToaster.hpp"
#include "XWingToast.hpp"
#include "TIEToast.hpp"

#include "LaserBolt.hpp"

class Sprites {

public:
    
    static Sprite * getNewRandom( map<string, vector<gl::Texture2dRef>> * textures, float scaling )
    {
        int r = randInt( 100 );

        if ( r > 90 )
        {
            return new PoliceToaster( textures, scaling );
        }
        else if ( r > 80 )
        {
            return new XWingToast( textures, scaling );
        }
        else if ( r > 70 )
        {
            return new TIEToast( textures, scaling );
        }
        else if ( r > 60 )
        {
            return new Toast( textures, scaling );
        }
        else if ( r > 50 )
        {
            return new ToastBurnt( textures, scaling );
        }
        else
        {
            return new Toaster( textures, scaling );
        }
    };
};

#endif /* Sprites_hpp */
