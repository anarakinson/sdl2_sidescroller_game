#pragma once 

#include <game.h>
#include <entity.h>
#include <tile.h>
#include <player.h>
#include <enemy.h>
#include <enemy_crab.h>
#include <background.h>

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>


namespace level1 {

    // add HoriZontal tile line
    void tile_hz_line(int x, int y, int len, SDL_Texture *tile_texture, Game &game) {
        for (int i = 0; i < len; ++i) {
            std::unique_ptr<Tile> tile{new Tile{x + i * 32, y, 32, 32, tile_texture}};
            if (i % 3 == 0) { tile->hflip(); }
            game.add_tile(std::move(tile));
        }
    }
    // add VerTical tile line
    void tile_vt_line(int x, int y, int len, SDL_Texture *tile_texture, Game &game) {
        for (int i = 0; i < len; ++i) {
            std::unique_ptr<Tile> tile{new Tile{x, y + i * 32, 32, 32, tile_texture}};
            if (i % 3 == 0) { tile->vflip(); }
            game.add_tile(std::move(tile));
        }
    }

    void load_level(Game &game) {

        /*--------------------------------------------------------------------------*/
        SDL_Texture *player_texture = TextureManager::LoadTexture("assets/player.png");
        SDL_Texture *tile_texture = TextureManager::LoadTexture("assets/solid.png");
        SDL_Texture *enemy_texture = TextureManager::LoadTexture("assets/packman_set.png");
        SDL_Texture *background_layer_texture_0 = TextureManager::LoadTexture("assets/Background/background.png");
        SDL_Texture *background_layer_texture_1 = TextureManager::LoadTexture("assets/Background/bg_2.png");

        // add player
        std::unique_ptr<Player> player{new Player{0, 0, 64, 64, player_texture}};
        game.add_player(std::move(player));

        // add background
        std::unique_ptr<Background> background_layer0{new Background{0, 0, game.window_width(), game.window_height(), background_layer_texture_0}};
        std::unique_ptr<Background> background_layer1{new Background{0, 0, game.window_width(), game.window_height(), background_layer_texture_1}};
        game.add_background_layer(std::move(background_layer0));
        game.add_background_layer(std::move(background_layer1));

        // add enemies
        // std::unique_ptr<Enemy> enemy{new Enemy{300, 300, 64, 64, enemy_texture}};
        // game.add_entity(std::move(enemy));

        { std::unique_ptr<EnemyCrab> enemy{new EnemyCrab{700, 300, 32, 42, enemy_texture} };
        game.add_entity(std::move(enemy));}
        { std::unique_ptr<EnemyCrab> enemy{new EnemyCrab{800 * 2, 300, 32, 42, enemy_texture} };
        game.add_entity(std::move(enemy));}

        for (int i = 0; i < 3; ++i) {
            std::unique_ptr<Enemy> enemy{new Enemy{1200 + i * 10, 300 + i, 32, 32, enemy_texture}};
            game.add_entity(std::move(enemy));
        }

        // add tiles

        for (int i = 0; i < 5; ++i) {
            std::unique_ptr<Tile> tile{new Tile{i * 90 + 150, 200, 90, 90 - i * 5, tile_texture}};
            game.add_tile(std::move(tile));
        }

        tile_hz_line(-50, 500, 1200, tile_texture, game);
        tile_hz_line(-50, -10, 120, tile_texture, game);
        tile_vt_line(-50, -100, 20, tile_texture, game);

        std::unique_ptr<Tile> tile2{new Tile{164, 500-32, 32, 32, tile_texture}};
        game.add_tile(std::move(tile2));
        std::unique_ptr<Tile> tile3{new Tile{196, 500-32, 32, 32, tile_texture}};
        game.add_tile(std::move(tile3));
        std::unique_ptr<Tile> tile4{new Tile{328, 500-32, 32, 32, tile_texture}};
        game.add_tile(std::move(tile4));


        tile_hz_line(700, 500-32, 12, tile_texture, game);
        tile_hz_line(760, 500-64, 8, tile_texture, game);
        tile_hz_line(800, 500-96, 3, tile_texture, game);

        tile_hz_line(1200, 500-32, 18, tile_texture, game);
        tile_hz_line(1270, 500-64, 8, tile_texture, game);

        tile_hz_line(680, 280, 3, tile_texture, game);
        
    }

} // namespace level1