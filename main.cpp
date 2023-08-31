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
constexpr static int UPS = 240;  
constexpr static int update_delay = 1000 / UPS;
// set frame rate
constexpr static int FPS = 60;   
constexpr static int frame_delay = 1000 / FPS;


int main() {

    // gametest::test();

    static Game game;
    game.init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height);

    /*--------------------------------------------------------------------------*/
    SDL_Texture *tile_texture = TextureManager::LoadTexture("assets/solid.png");
    SDL_Texture *enemy_texture = TextureManager::LoadTexture("assets/packman_set.png");

    // add enemies
    std::unique_ptr<Enemy> enemy{new Enemy{100, 100, 64, 64, enemy_texture}};
    game.add_entity(std::move(enemy));

    for (int i = 0; i < 5; ++i) {
        std::unique_ptr<Enemy> enemy1{new Enemy{100 + i, 100 + i, 32, 32, enemy_texture}};
        game.add_entity(std::move(enemy1));
    }

    // add tiles
    for (int i = 0; i < 5; ++i) {
        std::unique_ptr<Tile> tile{new Tile{i * 90 + 150, 200, 90, 90, tile_texture}};
        game.add_tile(std::move(tile));
    }
    for (int i = 0; i < 120; ++i) {
        std::unique_ptr<Tile> tile1{new Tile{i * 64 - 50, 500, 64, 64, tile_texture}};
        if (i % 3 == 0) { tile1->hflip(); }
        game.add_tile(std::move(tile1));
    }
    for (int i = 0; i < 120; ++i) {
        std::unique_ptr<Tile> tile1{new Tile{i * 64 - 50, -10, 64, 64, tile_texture}};
        game.add_tile(std::move(tile1));
    }
    for (int i = 0; i < 120; ++i) {
        std::unique_ptr<Tile> tile1{new Tile{-50, i * 64 - 100, 64, 64, tile_texture}};
        game.add_tile(std::move(tile1));
    }

    std::unique_ptr<Tile> tile2{new Tile{164, 500-64, 64, 64, tile_texture}};
    game.add_tile(std::move(tile2));
    std::unique_ptr<Tile> tile3{new Tile{228, 500-64, 64, 64, tile_texture}};
    game.add_tile(std::move(tile3));
    std::unique_ptr<Tile> tile4{new Tile{328, 500-64, 64, 64, tile_texture}};
    game.add_tile(std::move(tile4));
    
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

    return 0;

}
