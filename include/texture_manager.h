#pragma once 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class TextureManager {
public:
    static SDL_Texture *LoadTexture(const char *filename) {
    
        SDL_Surface *temp_surface = IMG_Load(filename);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
        SDL_FreeSurface(temp_surface);

        return texture;    

    }

    static void Draw(SDL_Texture *texture, SDL_Rect src_rect, SDL_Rect dst_rect) {
        SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
    }

    static SDL_Renderer *renderer;

};


class ProjectileTexture {
public:
    static SDL_Texture *projectile_bubble_texture;

    static void load_textures() {
        projectile_bubble_texture = TextureManager::LoadTexture("assets/projectiles/bubble.png");
    }

};



// class Texture {
// public:
//     static SDL_Texture *projectile_bubble_texture;
//     static SDL_Texture *player_texture;
//     static SDL_Texture *tile_texture;
//     static SDL_Texture *enemy_texture;
//     static SDL_Texture *background_layer_texture_0;
//     static SDL_Texture *background_layer_texture_1;

// };

