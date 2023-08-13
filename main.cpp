#include <test.h>
#include <game.h>
#include <entity.h>
#include <player.h>
#include <enemy.h>

#include <iostream>
#include <SDL2/SDL.h>

#undef main


// set window size
constexpr static int width = 800;
constexpr static int height = 600;
// set frame rate
constexpr static int FPS = 60;
constexpr static int frame_delay = 1000 / FPS;


int main() {

    // gametest::test();

    static Game game;
    game.init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);

    // std::unique_ptr<Player> player{new Player{0, 0, "assets/packman_set.png"}};
    // game.add_entity(std::move(player));
    std::unique_ptr<Enemy> enemy{new Enemy{100, 100, "assets/packman_set.png"}};
    game.add_entity(std::move(enemy));

    // set frame rate variables
    uint32_t frame_start;
    int frame_duration;

    while (game.is_running()) {
        // get frame start time
        frame_start = SDL_GetTicks();

        // handle user input
        game.handle_events();

        // update all objects
        game.update();

        // display changes
        game.render();

        // get frame duration
        frame_duration = SDL_GetTicks() - frame_start;
        // if frame duration too short - force frame delay
        if (frame_duration < frame_delay) {
            SDL_Delay(frame_delay - frame_duration);
        }
    }

    game.clean();

    return 0;

}