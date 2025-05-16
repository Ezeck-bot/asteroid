#include "Projectile.h"
#include <raylib.h>
#include <math.h>

Projectile::Projectile(float start_x, float start_y, float angle_deg, float ship_speed, float ship_velocity_x, float ship_velocity_y)
    : GameObject({ start_x, start_y }, { 0.0f, 0.0f }, 4.0f) {
    float rad = angle_deg * DEG2RAD;
    float projectile_speed = 400.0f;
    velocity.x = sinf(rad) * projectile_speed + ship_velocity_x;
    velocity.y = -cosf(rad) * projectile_speed + ship_velocity_y;
    lifetime = 2.0f;
}

void Projectile::update(float dt) {
    if (!active) {
        return;
    }
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    lifetime -= dt;
    if (position.x < 0 || position.x > 800 || position.y < 0 || position.y > 700 || lifetime <= 0) {
        active = false;
    }
}

void Projectile::draw() const {
    if (active) {
        DrawCircleV(position, radius, RAYWHITE);
    }
}



