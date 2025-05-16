#include "GameObject.h"

GameObject::GameObject(Vector2 pos, Vector2 vel, float r)
    : position(pos), velocity(vel), radius(r), active(true) {
}