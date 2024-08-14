#pragma once

#include "DynamicEntity.h"

class FrozenTektike : public DynamicEntity {
    private:
        int counter;
        const int WAITING_TIME = 32;  // 60; //Since its moving less time, we decided to reduce wait time to acompensate 
        const int MOVEMENT_TIME = 16;  //30; //To force results of move to be a factor of 48, which is the size of a tile.
        int linkX;
        int linkY;
        
        
        int lastX;
        int lastY;
        int beforeLastX;
        int beforeLastY;

        bool lastUP = false;
        bool lastDOWN = false;
        bool lastRIGHT = false;
        bool lastLEFT = false;

        bool beforelastUP = false;
        bool beforelastDOWN = false;
        bool beforelastRIGHT = false;
        bool beforelastLEFT = false;
        

        // int linkLastX;
        // int linkLastY;

    public: 
        FrozenTektike(int x, int y, shared_ptr<Handler> handler, shared_ptr<DynamicEntityAnimations> animations) : DynamicEntity(x, y, handler, animations) {
            this->MAX_HEALTH = 1;
            this->health = MAX_HEALTH;
            this->counter = 0;
            // this->lastX = x;
            // this->lastY = y;
        };

        void update();
        void damage(int damage);
        void onDeath();
        void onCollision(shared_ptr<DynamicEntity> entity);
        void setLinkX(int linkX);
        void setLinkY(int linkY);
        //void revive();       
};
