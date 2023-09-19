#include <test.h>
#include <game.h>
#include <levels/level1.h>

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>

#undef main


// global parameters
namespace global {

    // set window size
    constexpr static int width = 800;
    constexpr static int height = 600;
    // set updates per second
    constexpr static int UPS = 120;  
    constexpr static int update_delay = 1000 / UPS;
    // set frame rate
    constexpr static int FPS = 60;   
    constexpr static int frame_delay = 1000 / FPS;

    float UOF = 2; 

} // namespace global

int main() {

    // gametest::test();

    // init game
    Game game{"game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, global::width, global::height};
    
    // load content
    level1::load_level(game);
    
    /*---------------------------------------------------------------------------*/
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
        if (SDL_GetTicks() - frame_counter >= global::frame_delay) {
            game.render();

            frame_counter = SDL_GetTicks();
        }

        // get frame duration
        update_duration = SDL_GetTicks() - update_start;
        // if frame duration too short - force frame delay
        if (update_duration < global::update_delay) {
            SDL_Delay(global::update_delay - update_duration);
        }
    }

    return 0;

}
