#include <test.h>
#include <game.h>
#include <entity.h>
#include <player.h>
#include <enemy.h>
#include <levels/level1.h>

#include <iostream>
#include <SDL2/SDL.h>

#undef main


// set window size
constexpr static int width = 800;
constexpr static int height = 600;
// set updates per second
constexpr static int UPS = 300;  
constexpr static int update_delay = 1000 / UPS;
// set frame rate
constexpr static int FPS = 60;   
constexpr static int frame_delay = 1000 / FPS;


int main() {

    // gametest::test();

    static Game game;
    game.init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);

    // add enemies
    std::unique_ptr<Enemy> enemy{new Enemy{100, 100, 64, 64, "assets/packman_set.png"}};
    game.add_entity(std::move(enemy));

    // add tiles
    for (int i = 0; i < 5; ++i) {
        std::unique_ptr<Tile> tile{new Tile{i * 90 + 150, 100, 90, 90, "assets/solid.png"}};
        game.add_entity(std::move(tile));
    }
    for (int i = 0; i < 10; ++i) {
        std::unique_ptr<Tile> tile1{new Tile{i * 64 + 50, 400, 64, 64, "assets/solid.png"}};
        game.add_entity(std::move(tile1));
    }
    std::unique_ptr<Tile> tile2{new Tile{164, 400-64, 64, 64, "assets/solid.png"}};
    game.add_entity(std::move(tile2));
    std::unique_ptr<Tile> tile3{new Tile{228, 400-64, 64, 64, "assets/solid.png"}};
    game.add_entity(std::move(tile3));
    
    // set frame rate variables
    uint32_t update_start;
    uint32_t frame_counter = SDL_GetTicks();
    int update_duration;

    while (game.is_running()) {
        // get frame start time
        update_start = SDL_GetTicks();

        // handle user input
        game.handle_events();

        // update all objects
        game.update();

        // display changes
        if (SDL_GetTicks() - frame_counter >= frame_delay) {
            game.render();
            frame_counter = SDL_GetTicks();
        }

        // get frame duration
        update_duration = SDL_GetTicks() - update_start;
        // if frame duration too short - force frame delay
        if (update_duration < update_delay) {
            SDL_Delay(update_delay - update_duration);
        }
    }

    game.clean();

    return 0;

}
