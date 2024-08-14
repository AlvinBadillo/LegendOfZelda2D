#include "FrozenTektike.h"

void FrozenTektike::update(){
    
    counter++;

    // It is time to stop moving
    if (movingDir[UP] || movingDir[DOWN] || movingDir[LEFT] || movingDir[RIGHT]){
        if (counter == MOVEMENT_TIME){

            this->speed = Handler::PIXEL_SCALE;

            beforelastDOWN = lastDOWN;
            beforelastUP = lastUP;
            beforelastRIGHT = lastRIGHT;
            beforelastLEFT = lastLEFT; 

            lastUP = movingDir[UP];
            lastDOWN = movingDir[DOWN];
            lastRIGHT = movingDir[RIGHT];
            lastLEFT = movingDir[LEFT];

            movingDir[UP] = false;
            movingDir[DOWN] = false;
            movingDir[LEFT] = false;
            movingDir[RIGHT] = false;
            counter = 0;
        }
    }

    else{
        // Time to move in a random direction
        if (counter == WAITING_TIME){
            // movingDir[UP] = false;
            // movingDir[DOWN] = false;
            // movingDir[LEFT] = false;
            // movingDir[RIGHT] = false;
            // Direction direction = static_cast<Direction>(ofRandom(4));
            // movingDir[direction] = true;
            // counter = 0;

            //TODO: tackle spacial cases and aling to pass trough narrow spaces

            movingDir[UP] = false;
            movingDir[DOWN] = false;
            movingDir[LEFT] = false;
            movingDir[RIGHT] = false;

            int xdiff = linkX - this->getX();
            int ydiff = linkY - this->getY();

            bool specialCase = false;

            if(this->getX() == lastX && this->getX() == beforeLastX && this->getY() == lastY && this->getY() == beforeLastY){
                this->speed = this->speed * 3;
                int random = ofRandom(2);
                if(random == 1){
                    if(xdiff > 0){
                        movingDir[LEFT] = true;
                    }
                    else{
                        movingDir[RIGHT] = true;
                    } 
                }
                else{
                    if(ydiff > 0){
                        movingDir[UP] = true;
                    }
                    else{
                        movingDir[DOWN] = true;
                    }
                }
                specialCase = true;
            }
            else if(lastUP || lastDOWN){         //was trying to move on Y
                if(this->getY() == lastY){ //did not move on Y
                    if(xdiff > 0){
                        movingDir[RIGHT] = true;

                    }
                    else{
                        movingDir[LEFT] = true;
                    }      
                    specialCase = true;             
                }
            }
            else if(lastRIGHT || lastLEFT){      //was trying to move on X
                if(this->getX() == lastX){   //did not move on X
                    if(ydiff > 0){
                        movingDir[DOWN] = true;
                    }
                    else{
                        movingDir[UP] = true;
                    }
                    specialCase = true;
                }
            }
            if(!specialCase){
                if(abs(xdiff) > abs(ydiff)){
                    //we move in x
                    if(xdiff > 0){
                        movingDir[RIGHT] = true;

                    }
                    else{
                        movingDir[LEFT] = true;
                    }
                }
                else{
                    //we move in y
                    if(ydiff > 0){
                        movingDir[DOWN] = true;
                    }
                    else{
                        movingDir[UP] = true;
                    }
                }
            }
            beforeLastX = lastX;
            beforeLastY = lastY;
            lastX = this->getX();
            lastY = this->getY();
            counter = 0;
        }
    }

    DynamicEntity::update();
}

void FrozenTektike::damage(int damage){
    if (dead) return;
    // Play the damage sound if we're about to take damage
    if (invincibilityFrames == 0)
        handler->getSoundEffectManager()->playSoundEffect("enemy_hurt");
        
    DynamicEntity::damage(damage);
}

void FrozenTektike::onDeath(){
    handler->getSoundEffectManager()->playSoundEffect("enemy_death");
}

void FrozenTektike::onCollision(shared_ptr<DynamicEntity> e){
    if(!dead)
        e->damage(30);
}

void FrozenTektike::setLinkX(int linkX){
    this->linkX = linkX;
}
void FrozenTektike::setLinkY(int linkY){
    this->linkY = linkY;
}