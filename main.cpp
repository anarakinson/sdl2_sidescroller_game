#include <test.h>
#include <game.h>
#include <game_object.h>

#include <iostream>
#include <SDL2/SDL.h>

#undef main


// set window size
constexpr static int width = 800;
constexpr static int height = 600;
// set frame rate
constexpr static int FPS = 60;
constexpr static int frame_delay = 1000 / FPS;

gameloop::Game *game = nullptr;            // creating game on heap for not eating all memory from stack


int main() {

    // gametest::test();

    game = new gameloop::Game{};
    game->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);


    // set frame rate variables
    uint32_t frame_start;
    int frame_duration;

    while (game->is_running()) {
        // get frame start time
        frame_start = SDL_GetTicks();

        // handle user input
        game->handle_events();

        // update all objects
        game->update();

        // display changes
        game->render();

        // get frame duration
        frame_duration = SDL_GetTicks() - frame_start;
        // if frame duration too short - force frame delay
        if (frame_duration < frame_delay) {
            SDL_Delay(frame_delay - frame_duration);
        }
    }

    game->clean();

    return 0;

}