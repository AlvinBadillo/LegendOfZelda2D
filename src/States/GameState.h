#pragma once

#include "Animation.h"
#include "Link.h"
#include "Tektike.h"
#include "FrozenTektike.h"
#include "Sword.h" 
#include "MapBuilder.h"
#include "State.h"
#include <memory>

class GameState : public State {

private:
    shared_ptr<Map> currentMap;
    shared_ptr<Map> overWorldMap;
    shared_ptr<Map> oldManCaveMap;
    shared_ptr<Map> dungeonMap;
    unique_ptr<MapBuilder> mapBuilder;
    shared_ptr<Sword> swordItem;
    bool swordExist = false;
   
public:
    GameState(shared_ptr<Handler> handler) : State(handler) { this->reset(); }
    void update();
    void draw();
    void reset();
    void keyPressed(int key);
    void keyReleased(int key);
    ofImage menuHUD;
    bool paused;
    int hudY;
    int hudH;
    int hudHeight;
    int changeState;

    shared_ptr<Tektike> createTektike();
    shared_ptr<Sword> createSword(); 
    shared_ptr<FrozenTektike> createFrozenTektike();
    
};