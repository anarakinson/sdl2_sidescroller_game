#pragma once 

#include <game.h>
#include <entity.h>
#include <tile.h>
#include <player.h>
#include <enemy.h>
#include <background.h>

#include <iostream>
#include <SDL2/SDL.h>


namespace level1 {

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
        for (int i = 0; i < 1200; ++i) {
            std::unique_ptr<Tile> tile1{new Tile{i * 64 - 50, 500, 64, 64, tile_texture}};
            if (i % 3 == 0) { tile1->hflip(); }
            game.add_tile(std::move(tile1));
        }
        for (int i = 0; i < 120; ++i) {
            std::unique_ptr<Tile> tile1{new Tile{i * 64 - 50, -10, 64, 64, tile_texture}};
            game.add_tile(std::move(tile1));
        }
        for (int i = 0; i < 20; ++i) {
            std::unique_ptr<Tile> tile1{new Tile{-50, i * 64 - 100, 64, 64, tile_texture}};
            game.add_tile(std::move(tile1));
        }

        std::unique_ptr<Tile> tile2{new Tile{164, 500-64, 64, 64, tile_texture}};
        game.add_tile(std::move(tile2));
        std::unique_ptr<Tile> tile3{new Tile{228, 500-64, 64, 64, tile_texture}};
        game.add_tile(std::move(tile3));
        std::unique_ptr<Tile> tile4{new Tile{328, 500-64, 64, 64, tile_texture}};
        game.add_tile(std::move(tile4));

    }

} // namespace level1