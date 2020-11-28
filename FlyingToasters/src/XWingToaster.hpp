#ifndef XWingToaster_hpp
#define XWingToaster_hpp

#include "Item.hpp"

class XWingToaster: public Item {
    
public:
    
    XWingToaster();
  
    void update( double, std::vector<Item *> *, std::vector<Item *> * ) override;
    
private:
    
    bool switch_ = false;
    
    int burstCount_ = 0;
    int burstLength_ = 0;
    
    double lastShot_ = 0;
    
    bool firingBurst_ = false;
};

#endif /* XWingToaster_hpp */
