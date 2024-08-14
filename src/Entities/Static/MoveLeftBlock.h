#pragma once

#include "StaticEntity.h"
#include <memory>

class MoveLeftBlock : public StaticEntity {
public:
    MoveLeftBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~MoveLeftBlock(){};
    void onCollision(shared_ptr<DynamicEntity> e) {
        moveRecursive(e, 2);
    }
    int moveRecursive(shared_ptr<DynamicEntity> e, int timer){
        if(timer == 0){
            return 0;
        }
        else{
            e->setX(e->getX() - 1);
            return 1 + moveRecursive(e, timer - 1);
        }
    }
};