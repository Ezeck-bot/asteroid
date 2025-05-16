#include "Game.h"

Game::Game(int width, int height)
    : screenWidth(width), screenHeight(height) {
}

    void Game::update(float dt){
        for (int i = 0; i < objects.size(); i++)
        {
            objects[i]->update(dt);
        }
        
    }
    void Game::draw(){
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i]->IsActive())
            {
                objects[i]->draw();
            }
            
        }
        
    }