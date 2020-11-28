#ifndef TieFighterToaster_hpp
#define TieFighterToaster_hpp

#include "Item.hpp"

class TieFighterToaster: public Item {
    
public:
    
    TieFighterToaster();
    
    void update( double, std::vector<Item *> *, std::vector<Item *> * ) override;
    
private:
    
    int burstCount_ = 0;
    int burstLength_ = 0;
    
    double lastShot_ = 0;
    
    bool firingBurst_ = false;
};

#endif /* TieFighterToaster_hpp */
