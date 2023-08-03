#include <test.h>
#include <game.h>

#include <iostream>
#include <SDL2/SDL.h>

#undef main


constexpr static int width = 800;
constexpr static int height = 600;
constexpr static bool foolscreen = false;

gameloop::Game *game = nullptr;            // creating game on heap for not eating all memory from stack


int main() {

    // gametest::test();

    game = new gameloop::Game{};
    game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, foolscreen);

    while (game->is_running()) {
        // handle user input
        game->handle_events();

        // update all objects
        game->update();

        // display changes
        game->render();

        break;
    }

    game->clean();

    return 0;

}