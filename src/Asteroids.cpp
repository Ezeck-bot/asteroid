#include "Asteroids.h"
#include <raylib.h>
#include <algorithm>

Asteroids::Asteroids(int width, int height)
    : Game(width, height), vaisseau(nullptr), projectiles(), meteore(), soucoupes(), spawnTimerMeteore(0.0f), spawnTimerSoucoupe(0.0f), spawnIntervalMeteore(1.5f), spawnIntervalSoucoupe(15.0f), gameOver(false), points(0) {
}

Asteroids::~Asteroids() {
    for (auto obj : objects) {
        delete obj;
    }
    objects.clear();
    projectiles.clear();
    meteore.clear();
    soucoupes.clear();
}

void Asteroids::init() {
    InitWindow(screenWidth, screenHeight, "Astéroïdes");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)GetTime());

    vaisseau = new Vaisseau();
    objects.push_back(vaisseau);
}

void Asteroids::update(float dt) {
    Game::update(dt);
    if (gameOver) {
        return;
    }

    vaisseau->update(dt);

    // Récupérer les nouveaux projectiles créés par le vaisseau
    std::vector<Projectile*>& newProjectiles = vaisseau->getNewProjectiles();
    for (auto proj : newProjectiles) {
        projectiles.push_back(proj);
        objects.push_back(proj);
    }
    newProjectiles.clear(); // Vider la liste temporaire

    //collision
    CheckCollisionsMeteore();
    CheckCollisionsSoucoupe();

    //supprimer les objets inactifs
    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [](const Projectile* p) { return !p->IsActive(); }),
        projectiles.end()
    );

    meteore.erase(
        std::remove_if(meteore.begin(), meteore.end(),
            [](const Meteore* a) { return !a->IsActive(); }),
            meteore.end()
    );

    soucoupes.erase(
        std::remove_if(soucoupes.begin(), soucoupes.end(),
            [](const Soucoupe* s) { return !s->IsActive(); }),
        soucoupes.end()
    );

    objects.erase(
        std::remove_if(objects.begin(), objects.end(),
            [](const GameObject* o) { return !o->IsActive(); }),
        objects.end()
    );

    //générer les Météores et soucoupes
    spawnTimerMeteore -= dt;
    if (spawnTimerMeteore <= 0) {
        SpawnMeteore();
        spawnTimerMeteore = spawnIntervalMeteore;
    }

    spawnTimerSoucoupe -= dt;
    if (spawnTimerSoucoupe <= 0) {
        SpawnSoucoupe();
        spawnTimerSoucoupe = spawnIntervalSoucoupe;
    }
}

void Asteroids::draw() {

    BeginDrawing();
    ClearBackground(BLACK);
    Game::draw();
    if (gameOver) {
        DrawText("GAME OVER", screenWidth / 4, screenHeight / 2, 80, RED);
    }

    if (vaisseau->getNumberForLife() == 4)
    {
        DrawText("I I I I", 10, 10, 30, RED);
    } else if (vaisseau->getNumberForLife() == 3)
    {
        DrawText("I I I", 10, 10, 30, RED);
    } else if (vaisseau->getNumberForLife() == 2)
    {
        DrawText("I I", 10, 10, 30, RED);
    } else if (vaisseau->getNumberForLife() == 1)
    {
        DrawText("I", 10, 10, 30, RED);
    }
    
    

    DrawText(TextFormat("Point: %d", (int)points), 10, 40, 20, BLUE);
    EndDrawing();
}

void Asteroids::deinit() {
    CloseWindow();
}

bool Asteroids::not_finished() const {
    return !WindowShouldClose();
}

void Asteroids::SpawnMeteore() {
    int side = GetRandomValue(0, 3);
    float start_x, start_y;
    float dir_x, dir_y;

    switch (side) {
    case 0: // Haut
        start_x = GetRandomValue(0, screenWidth);
        start_y = 0;
        dir_x = GetRandomValue(-100, 100) / 100.0f;
        dir_y = GetRandomValue(50, 100) / 100.0f;
        break;
    case 1: // Droite
        start_x = screenWidth;
        start_y = GetRandomValue(0, screenHeight);
        dir_x = GetRandomValue(-100, -50) / 100.0f;
        dir_y = GetRandomValue(-100, 100) / 100.0f;
        break;
    case 2: // Bas
        start_x = GetRandomValue(0, screenWidth);
        start_y = screenHeight;
        dir_x = GetRandomValue(-100, 100) / 100.0f;
        dir_y = GetRandomValue(-100, -50) / 100.0f;
        break;
    case 3: // Gauche
        start_x = 0;
        start_y = GetRandomValue(0, screenHeight);
        dir_x = GetRandomValue(50, 100) / 100.0f;
        dir_y = GetRandomValue(-100, 100) / 100.0f;
        break;
    }

    Meteore* newAsteroid = new Meteore(start_x, start_y, dir_x, dir_y, 40.0f, 1, 14.0f);
    meteore.push_back(newAsteroid);
    objects.push_back(newAsteroid);
}

void Asteroids::SpawnSoucoupe() {
    int side = GetRandomValue(0, 3);
    float start_x, start_y;
    float dir_x, dir_y;

    switch (side) {
    case 0: // Haut
        start_x = GetRandomValue(0, screenWidth);
        start_y = 0;
        dir_x = GetRandomValue(-100, 100) / 100.0f;
        dir_y = GetRandomValue(50, 100) / 100.0f;
        break;
    case 1: // Droite
        start_x = screenWidth;
        start_y = GetRandomValue(0, screenHeight);
        dir_x = GetRandomValue(-100, -50) / 100.0f;
        dir_y = GetRandomValue(-100, 100) / 100.0f;
        break;
    case 2: // Bas
        start_x = GetRandomValue(0, screenWidth);
        start_y = screenHeight;
        dir_x = GetRandomValue(-100, 100) / 100.0f;
        dir_y = GetRandomValue(-100, -50) / 100.0f;
        break;
    case 3: // Gauche
        start_x = 0;
        start_y = GetRandomValue(0, screenHeight);
        dir_x = GetRandomValue(50, 100) / 100.0f;
        dir_y = GetRandomValue(-100, 100) / 100.0f;
        break;
    }

    Soucoupe* newSoucoupe = new Soucoupe(start_x, start_y, dir_x, dir_y);
    soucoupes.push_back(newSoucoupe);
    objects.push_back(newSoucoupe);
}

void Asteroids::CheckCollisionsMeteore(){
    for (auto proj : projectiles) {
        if (!proj->IsActive()) {
            continue;
        }
        for (auto asteroid : meteore) {
            if (!asteroid->IsActive()) {
                continue;
            }
            if (CheckCollisionCircles(proj->GetPosition(), proj->GetRadius(),
                                     asteroid->GetPosition(), asteroid->GetRadius())) {
                proj->SetActive(false);
                asteroid->SetActive(false);
                
                if (asteroid->getMeteoreType() == 1)
                {
                    points += 1000;
                } else if (asteroid->getMeteoreType() == 2) {
                    points += 1500;
                }

                //Faire disparaître l'ancien et créer deux nouveaux
                float newRadius = asteroid->GetRadius() * 0.5f;

                //pour ne pas que j'ai de très petit méteore
                if (newRadius >= 15.0f) {
                    Vector2 pos = asteroid->GetPosition();

                    float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
                    float offsetAngle = 30.0f * DEG2RAD;
                    Vector2 dir1 = { cosf(angle + offsetAngle), sinf(angle + offsetAngle) };
                    Vector2 dir2 = { cosf(angle - offsetAngle), sinf(angle - offsetAngle) };

                    Meteore* newAsteroid1 = new Meteore(pos.x, pos.y, dir1.x, dir1.y, newRadius, 2, 25.0f);
                    Meteore* newAsteroid2 = new Meteore(pos.x, pos.y, dir2.x, dir2.y, newRadius, 2, -70.0f);
                    meteore.push_back(newAsteroid1);
                    meteore.push_back(newAsteroid2);

                    objects.push_back(newAsteroid1);
                    objects.push_back(newAsteroid2);
                }
            }
        }
    }

    for (auto asteroid : meteore) {
        if (!asteroid->IsActive()) {
            continue;
        }
        if (CheckCollisionCircles(vaisseau->GetPosition(), vaisseau->GetRadius(),
                                 asteroid->GetPosition(), asteroid->GetRadius())) {
            vaisseau->setNumberForLife(vaisseau->getNumberForLife() - 1);
            vaisseau->resetPosition();
            if (vaisseau->getNumberForLife() <= 0) {
                gameOver = true;
            }
        }
    }
}

void Asteroids::CheckCollisionsSoucoupe(){
    for (auto proj : projectiles) {
        if (!proj->IsActive()) {
            continue;
        }
        for (auto soucoupe : soucoupes) {
            if (!soucoupe->IsActive()) {
                continue;
            }
            if (CheckCollisionCircles(proj->GetPosition(), proj->GetRadius(),
                                     soucoupe->GetPosition(), soucoupe->GetRadius())) {
                proj->SetActive(false);
                soucoupe->SetActive(false);

                points += 3000;
            }
        }
    }

    for (auto soucoupe : soucoupes) {
        if (!soucoupe->IsActive()) {
            continue;
        }
        if (CheckCollisionCircles(vaisseau->GetPosition(), vaisseau->GetRadius(),
                                    soucoupe->GetPosition(), soucoupe->GetRadius())) {
            vaisseau->setNumberForLife(vaisseau->getNumberForLife() - 1);
            vaisseau->resetPosition();
            soucoupe->SetActive(false);
            if (vaisseau->getNumberForLife() <= 0) {
                gameOver = true;
            }
        }
    }
}