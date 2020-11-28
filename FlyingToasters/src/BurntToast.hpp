#ifndef BurntToast_hpp
#define BurntToast_hpp

#include "Item.hpp"

class BurntToast: public Item {
    
public:
    
    BurntToast();
    
    void update( double, std::vector<Item *> *, std::vector<Item *> * ) override;
    
};

#endif /* BurntToast_hpp */
