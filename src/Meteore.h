#pragma once
#include "GameObject.h"
#include <cstdlib>

class Meteore : public GameObject {
private:
    Color couleurs[11];
    int randomNum = rand() % 7;
    int meteoreType;
public:
    Meteore(float start_x, float start_y, float dir_x, float dir_y, float radius, int meteoreType, float speed);
    void update(float dt) override;
    void draw() const override;
    int getMeteoreType() const { return meteoreType; }
};