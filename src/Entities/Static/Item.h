#pragma once

#include "StaticEntity.h"
#include <memory>
#include "Link.h"

class Link;

class Item : public StaticEntity {

    protected:
        bool isCollected;


    public:
        Item(int x, int y, shared_ptr<Handler> handler, ofImage sprite) : StaticEntity(x, y, handler) {
            this->currentSprite = sprite;
            isCollected = false;
        }
        ~Item(){};
        void onCollision(shared_ptr<DynamicEntity> e);
        virtual void applyEffect(shared_ptr<Link> link) = 0;
        bool getIsCollected(){return isCollected;}
        // int getX() { return x; }
        // int getY() { return y; }
        // int getWidth() { return width; }
        // int getHeight() { return height; }       

};