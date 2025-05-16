#pragma once
#include "Game.h"
#include "Vaisseau.h"
#include "Projectile.h"
#include "Meteore.h"
#include "Soucoupe.h"
#include <vector>

class Asteroids : public Game {
private:
    Vaisseau* vaisseau;
    std::vector<Projectile*> projectiles;
    std::vector<Meteore*> meteore;
    std::vector<Soucoupe*> soucoupes;
    float spawnTimerMeteore;
    float spawnTimerSoucoupe;
    float spawnIntervalMeteore;
    float spawnIntervalSoucoupe;
    bool gameOver;
    int points;

public:
    Asteroids(int width, int height);
    ~Asteroids();
    void init() override;
    void update(float dt) override;
    void draw() override;
    void deinit() override;
    bool not_finished() const override;

private:
    int getPoints() const { return points; }
    void setPoints(int value) { points = value; }
    void CheckCollisionsMeteore();
    void CheckCollisionsSoucoupe();
    void SpawnMeteore();
    void SpawnSoucoupe();
};