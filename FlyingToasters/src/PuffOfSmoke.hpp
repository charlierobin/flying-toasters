#ifndef PuffOfSmoke_hpp
#define PuffOfSmoke_hpp

#include "Item.hpp"

class PuffOfSmoke: public Item {
    
public:
    
    PuffOfSmoke( cinder::vec3 );
    
    void update( double, std::vector<Item *> *, std::vector<Item *> * ) override;
    void draw() override;
    
private:
    
    int lifetime_ = 0;
    
};

#endif /* PuffOfSmoke_hpp */
