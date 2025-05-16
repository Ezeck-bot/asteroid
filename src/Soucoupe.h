#pragma once
#include "GameObject.h"

class Soucoupe : public GameObject {
private:
    float speed;

public:
    Soucoupe(float start_x, float start_y, float dir_x, float dir_y);
    void update(float dt) override;
    void draw() const override;
    float getSpeed() const { return speed; }
};