#pragma once
#include "GameObject.h"

class Projectile : public GameObject {
private:
    float lifetime;

public:
    Projectile(float start_x, float start_y, float angle_deg, float ship_speed, float ship_velocity_x, float ship_velocity_y);
    void update(float dt) override;
    void draw() const override;
};