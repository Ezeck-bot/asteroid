#include "Meteore.h"
#include <raylib.h>
#include <math.h>

Meteore::Meteore(float start_x, float start_y, float dir_x, float dir_y, float radius, int meteoreType, float speed)
    : GameObject({ start_x, start_y }, { 0.0f, 0.0f }, radius), couleurs{GREEN, PINK, PURPLE, GOLD, YELLOW, ORANGE} {
    //speed = 14.0f * (20.0f / radius);
    this->meteoreType = speed;
    this->meteoreType = meteoreType;
    float length = sqrtf(dir_x * dir_x + dir_y * dir_y);
    velocity.x = (length > 0) ? (dir_x / length) * speed : 0;
    velocity.y = (length > 0) ? (dir_y / length) * speed : 0;
}

void Meteore::update(float dt) {
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

void Meteore::draw() const {
    if (active) {
        DrawCircleV(position, radius, couleurs[randomNum]);
    }
}