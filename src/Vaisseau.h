#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Vaisseau : public GameObject {
private:
    int numberForLife;
    float rotate;
    float speed;
    float acceleration;
    float friction;
    float delay;
    std::vector<Projectile*> newProjectiles;
    //empêcher le tir en mitraillette
    static constexpr float elapsed = 1.0f;

public:
    Vaisseau();
    void update(float dt);
    void draw() const override;

    int getNumberForLife() const { return numberForLife; }
    float getRotate() const { return rotate; }
    void setNumberForLife(int value) { numberForLife = value; }
    void resetPosition();
    std::vector<Projectile*>& getNewProjectiles();
};