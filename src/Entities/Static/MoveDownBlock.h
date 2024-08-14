#pragma once

#include "StaticEntity.h"
#include <memory>

class MoveDownBlock : public StaticEntity {
public:
    MoveDownBlock(int x, int y, shared_ptr<Handler> handler) : StaticEntity(x, y, handler) {}
    ~MoveDownBlock(){};
    void onCollision(shared_ptr<DynamicEntity> e) {
        moveRecursive(e, 2);
    }
    int moveRecursive(shared_ptr<DynamicEntity> e, int timer){
        if(timer == 0){
            return 0;
        }
        else{
            e->setY(e->getY() + 1);
            return 1 + moveRecursive(e, timer - 1);
        }
    }
};