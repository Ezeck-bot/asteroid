#pragma once
#include <raylib.h>
#include "GameObject.h"
#include <vector>

class Game {
protected:
    int screenWidth;
    int screenHeight;
    std::vector<GameObject*> objects;
public:
    Game(int width, int height);
    virtual ~Game() = default;
    virtual void init() = 0;
    virtual void update(float dt);
    virtual void draw();
    virtual void deinit() = 0;
    virtual bool not_finished() const = 0;
};