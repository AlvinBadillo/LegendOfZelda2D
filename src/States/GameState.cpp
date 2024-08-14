#include "GameState.h"

void GameState::update()
{
    if(!paused){
        this->currentMap->update();
    }
    

    if(currentMap->isFinished()){
        currentMap->setFinished(false);
        if(currentMap->getWhereTo() == OVER_WORLD){
            //Set Link's X and Y coordinates relative to the coming map section's door positon
            currentMap->getPlayer()->setX(overWorldMap->getCurrentSection()->doorXPos);
            currentMap->getPlayer()->setY(overWorldMap->getCurrentSection()->doorYPos + Handler::TILE_HEIGHT);
            //Remove Link from being part of the Map to avoid multiple Links in diff maps.
            // For now we use the setter to have the same link in both maps
            overWorldMap->setPlayer(currentMap->getPlayer());
            currentMap = overWorldMap;
        }
        else if(currentMap->getWhereTo() == OLD_MANS_CAVE){
            currentMap->getPlayer()->setX(oldManCaveMap->getCurrentSection()->doorXPos);
            currentMap->getPlayer()->setY(oldManCaveMap->getCurrentSection()->doorYPos - Handler::TILE_HEIGHT);
            oldManCaveMap->setPlayer(currentMap->getPlayer());
            currentMap = oldManCaveMap;
        }
        else if(currentMap->getWhereTo() == DUNGEON){
            currentMap->getPlayer()->setX(dungeonMap->getCurrentSection()->doorXPos);                         
            currentMap->getPlayer()->setY(dungeonMap->getCurrentSection()->doorYPos - Handler::TILE_HEIGHT);
            dungeonMap->setPlayer(currentMap->getPlayer());
            currentMap = dungeonMap; //new map (Y)
        }
    }
    if(handler->pickedUpSword && !swordExist){
        swordExist = true;
        overWorldMap->getSection(2, 0)->addItemToTile(0, 0, swordItem);
        overWorldMap->getSection(3, 1)->addItemToTile(0, 0, swordItem);

        overWorldMap->getSection(0, 1)->addItemToTile(0, 0, swordItem);
        overWorldMap->getSection(4, 0)->addItemToTile(0, 0, swordItem);
        overWorldMap->getSection(1, 1)->addItemToTile(0, 0, swordItem);
    }  

}

void GameState::draw() {
    ofSetColor(255, 255, 255);
    currentMap->draw();

    // Change to Game Over
    if (currentMap->getPlayer()->isDead()) {
        ofImage gameOver = handler->getImageManager()->gameOverScreen;
        gameOver.draw(0, 0, ofGetWidth(), ofGetHeight());
        changeState++;
        if (changeState == 120) {
            this->setFinished(true);
            this->setNextState(GAME_OVER);
        }
    }

    if (paused) {
        // Full Screen HUD Transition Parameters
        hudHeight <= ofGetHeight() ? hudHeight += Handler::PIXEL_SCALE*2 : hudHeight;
        hudH <= 0 ? hudH += Handler::PIXEL_SCALE*2 : hudH;

    } else {
        // Small Screen HUD Transition Parameters
        hudHeight > ofGetHeight()/4 ? hudHeight -= Handler::PIXEL_SCALE*2 : hudHeight;
        hudH > -Handler::SECTION_HEIGHT ? hudH -= Handler::PIXEL_SCALE*2 : hudH;
    }
    handler->getImageManager()->HUD.draw(0, hudH, ofGetWidth(), ofGetHeight());

    // Draw hearts on the HUD
    this->currentMap->getPlayer()->drawHearts(hudHeight-10);

    // Draw Sword on the HUD
    if(Handler::pickedUpSword)
        handler->getImageManager()->basicSword.draw(ofGetWidth()/2 - (ofGetWidth() % 10), hudHeight - 90, 40, 40);

    // MiniMap
    ofDrawRectangle(this->currentMap->getPlayer()->getX()/20 + 40 * (currentMap->getCurrentSectionX()+1),  
                    hudHeight + (this->currentMap->getPlayer()->getY()/15  + 50 * (currentMap->getCurrentSectionY()+1)) - 175, 5, 5);
}

void GameState::reset() {
    this->musicFileName = "overworld.wav";
    mapBuilder = make_unique<MapBuilder>(handler);
    overWorldMap = mapBuilder->createMap(handler->getImageManager()->overWorldPixelMap);
    oldManCaveMap = mapBuilder->createMap(handler->getImageManager()->oldMansCavePixelMap);
    dungeonMap = mapBuilder->createMap(handler->getImageManager()->dungeonPixelMap);
    //If there's more than one section in a map, besides overWorld, we must set which section we want to start at
    oldManCaveMap->setCurrentSection(0,0);
    dungeonMap->setCurrentSection(0,1);

    swordItem = createSword(); 
    oldManCaveMap->getSection(0,0)->addItemToTile(3,6, swordItem);

    overWorldMap->getSection(2, 0)->addEnemyToTile(8, 4, createTektike());
    overWorldMap->getSection(2, 0)->addEnemyToTile(4, 4, createTektike());
    overWorldMap->getSection(3, 1)->addEnemyToTile(6, 4, createTektike());

    overWorldMap->getSection(0, 1)->addEnemyToTile(10, 3, createFrozenTektike());
    overWorldMap->getSection(4, 0)->addEnemyToTile(6, 3, createFrozenTektike());
    overWorldMap->getSection(1, 1)->addEnemyToTile(7, 7, createFrozenTektike());


    currentMap = overWorldMap;

    paused = false;
    hudH = -Handler::SECTION_HEIGHT;
    hudHeight = Handler::HUD_HEIGHT;
    changeState = 0;
    Handler::pickedUpSword = false;
    swordExist = false;
}

void GameState::keyPressed(int key) {
    if (key == 'p'){
        paused = !paused;
    } else {
        currentMap->keyPressed(key);
    }
}

void GameState::keyReleased(int key) {
    currentMap->keyReleased(key);
}

shared_ptr<Tektike> GameState::createTektike() {
    // getTekitkeAnimations() returns a NEW shared_ptr
    // This is so that all Tektikes will not point
    // to the same animation object and "super tick" 
    // each other
    return make_shared<Tektike>(0, 0, handler, handler->getImageManager()->getTektikeAnimations());
}

shared_ptr<Sword> GameState::createSword() { 

    return make_shared<Sword>(0, 0, handler, handler->getImageManager()->getSpriteFromEntitySheetAt(2, 4));
}

shared_ptr<FrozenTektike> GameState::createFrozenTektike(){
    return make_shared<FrozenTektike>(0, 0, handler, handler->getImageManager()->getFrozenTektikeAnimations());
}