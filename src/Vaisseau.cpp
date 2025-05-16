#include "Vaisseau.h"
#include <raylib.h>
#include <math.h>

Vaisseau::Vaisseau()
    : GameObject({ 400.0f, 350.0f }, { 0.0f, 0.0f }, 15.0f) {
    numberForLife = 4;
    rotate = 0.0f;
    speed = 0.0f;
    acceleration = 2.0f;
    friction = 0.99f;
    //empêcher le tir en mitraillette
    delay = 1.0f;
}

void Vaisseau::update(float dt) {
    // Rotation
    if (IsKeyDown(KEY_RIGHT)) {
        rotate += 200.0f * dt;
    }
    if (IsKeyDown(KEY_LEFT)) {
        rotate -= 200.0f * dt;
    }

    // Normaliser la rotation
    if (rotate >= 360.0f) {
        rotate -= 360.0f;
    }
    if (rotate < 0.0f) {
        rotate += 360.0f;
    }

    // Gestion de la vitesse
    float maxSpeed = 300.0f;
    if (IsKeyDown(KEY_UP)) {
        speed += acceleration * dt * 60.0f;
    }
    if (IsKeyDown(KEY_DOWN)) {
        speed -= acceleration * dt * 60.0f;
    }
    speed = fmaxf(-maxSpeed / 2, fminf(speed, maxSpeed));
    speed *= powf(friction, dt * 60.0f);

    // Mettre à jour la vitesse
    float rad = rotate * DEG2RAD;
    velocity.x = sinf(rad) * speed;
    velocity.y = -cosf(rad) * speed;

    // Mettre à jour la position
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Gestion du wrap-around
    if (position.x > 800) {
        position.x -= 800;
    }
    if (position.x < 0) {
        position.x += 800;
    }
    if (position.y > 700) {
        position.y -= 700;
    }
    if (position.y < 0) {
        position.y += 700;
    }

    // Gestion des tirs
    delay -= dt;
    if (IsKeyDown(KEY_SPACE) && delay <= 0) {
        Vector2 v1 = { 0, -30 };
        float rad = rotate * DEG2RAD;
        float p1_x = cosf(rad) * v1.x - sinf(rad) * v1.y + position.x;
        float p1_y = sinf(rad) * v1.x + cosf(rad) * v1.y + position.y;
        Projectile* newProjectile = new Projectile(p1_x, p1_y, rotate, speed, velocity.x, velocity.y);
        newProjectiles.push_back(newProjectile);
        delay = elapsed;
    }
}

void Vaisseau::draw() const {
    Vector2 v1 = { 0, -30 };
    Vector2 v2 = { -20, 20 };
    Vector2 v3 = { 20, 20 };
    float rad = rotate * DEG2RAD;
    Vector2 p1 = { cosf(rad) * v1.x - sinf(rad) * v1.y + position.x, sinf(rad) * v1.x + cosf(rad) * v1.y + position.y };
    Vector2 p2 = { cosf(rad) * v2.x - sinf(rad) * v2.y + position.x, sinf(rad) * v2.x + cosf(rad) * v2.y + position.y };
    Vector2 p3 = { cosf(rad) * v3.x - sinf(rad) * v3.y + position.x, sinf(rad) * v3.x + cosf(rad) * v3.y + position.y };
    if (active) {
        DrawTriangleLines(p1, p2, p3, WHITE);
    }
}

void Vaisseau::resetPosition() {
    position = { 400.0f, 350.0f };
    speed = 0.0f;
    velocity = { 0.0f, 0.0f };
}

std::vector<Projectile*>& Vaisseau::getNewProjectiles() {
    return newProjectiles;
}