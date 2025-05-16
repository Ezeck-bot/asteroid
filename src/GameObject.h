#pragma once
#include <raylib.h>

class GameObject {
protected:
    Vector2 position;   // Position de l'objet
    Vector2 velocity;   // Vitesse de l'objet
    float radius;       // Rayon pour les collisions
    bool active;        // Indique si l'objet est actif

public:
    GameObject(Vector2 pos, Vector2 vel, float r);
    virtual ~GameObject() = default;
    virtual void update(float dt) = 0;
    virtual void draw() const = 0;

    bool IsActive() const { return active; }
    void SetActive(bool value) { active = value; }
    Vector2 GetPosition() const { return position; }
    float GetRadius() const { return radius; }
    Vector2 GetVelocity() const { return velocity; }
    void SetPosition(Vector2 pos) { position = pos; }
    void SetVelocity(Vector2 vel) { velocity = vel; }
};