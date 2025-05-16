#include "Soucoupe.h"
#include <raylib.h>
#include <math.h>

Soucoupe::Soucoupe(float start_x, float start_y, float dir_x, float dir_y)
    : GameObject({ start_x, start_y }, { 0.0f, 0.0f }, 60.0f) {
    speed = 6.0f;
    float length = sqrtf(dir_x * dir_x + dir_y * dir_y);
    velocity.x = (length > 0) ? (dir_x / length) * speed : 0;
    velocity.y = (length > 0) ? (dir_y / length) * speed : 0;
}

void Soucoupe::update(float dt) {
    if (!active) {
        return;
    }
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
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
}

void Soucoupe::draw() const {
    if (active) {
        DrawRectangle(position.x - 10, position.y - 5, 60, 60, RED);
    }
}