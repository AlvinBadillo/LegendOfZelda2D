#pragma once

#include "Item.h"

class Sword : public Item{

    public:

        Sword(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : Item(x, y, handler, sprite){
            this->currentSprite = sprite;
            isCollected = false;
        }

        void applyEffect(shared_ptr<Link> link){

        }
        void onCollision(shared_ptr<DynamicEntity> e){      
            e->damage(1);
        }
        bool getIsCollected(){
            return isCollected;
        }
};