#ifndef LaserBolt_hpp
#define LaserBolt_hpp

#include "Item.hpp"

class LaserBolt: public Item {
    
public:
    
    LaserBolt( cinder::vec3, cinder::vec3 );
    
    void update( double, std::vector<Item *> *, std::vector<Item *> * ) override;
    void draw() override;
    
private:
    
    float speedMultiplier_ = 6;
  
    bool bodge = true;
    
    cinder::vec3 colour_;
    
};

#endif /* LaserBolt_hpp */
