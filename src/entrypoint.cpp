#include "entrypoint.h"
#include "Asteroids.h"

void raylib_start(void) {
    Game* game = new Asteroids(800, 700);
    game->init();
    while (game->not_finished()) {
        float dt = GetFrameTime();
        game->update(dt);
        game->draw();
    }
    game->deinit();
    delete game;
}