#pragma once 

#include <entity.h>
#include <player.h>
#include <texture_manager.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>


class UI {
public:
    UI() {

    }

    void update() {
        hitpoints = m_owner->hitpoints();
        max_hitpoints = m_owner->max_hitpoints();
        current_projectile_type = m_owner->current_projectile_type();
    }

    void render() {

        for (int i = 0; i < max_hitpoints; ++i) {
            health.empty_dst_rect.x = 25 * (i + 1) + 5;
            health.empty_dst_rect.y = 20;
            health.empty_dst_rect.w = 25;
            health.empty_dst_rect.h = 25;
            
            SDL_RenderCopyEx(
                TextureManager::renderer, 
                health.empty_texture, 
                &health.empty_src_rect, &health.empty_dst_rect, 
                health.angle, &health.center, health.flip
            );
        }

        for (int i = 0; i < hitpoints; ++i) {
            health.full_dst_rect.x = 25 * (i + 1) + 5;
            health.full_dst_rect.y = 20;
            health.full_dst_rect.w = 25;
            health.full_dst_rect.h = 25;
            
            SDL_RenderCopyEx(
                TextureManager::renderer, 
                health.full_texture, 
                &health.full_src_rect, &health.full_dst_rect, 
                health.angle, &health.center, health.flip
            );
        }
        
    }

    void attach(Player *owner) {
        m_owner = owner;
    }

    void set_health_texture(SDL_Texture *empty_t, SDL_Texture *full_t) {
        health.empty_texture = empty_t;
        health.full_texture = full_t;
    }

private:

    int m_counter = 0;
    Player *m_owner; 

    int hitpoints;
    int max_hitpoints;
    ProjectileType current_projectile_type;

    struct Health {

        Health() {
            empty_src_rect.x = 0;
            empty_src_rect.y = 0;
            empty_src_rect.w = 15;
            empty_src_rect.h = 11;

            full_src_rect.x = 0;
            full_src_rect.y = 0;
            full_src_rect.w = 15;
            full_src_rect.h = 11;
            
            empty_texture = TextureManager::LoadTexture("assets/UI/HeartUIEmpty.png");
            full_texture = TextureManager::LoadTexture("assets/UI/HeartUIFull.png");

        }
        ~Health() {
            SDL_DestroyTexture(empty_texture);
            SDL_DestroyTexture(full_texture);
        }

        double angle = 0;
        
        SDL_Rect empty_src_rect{}; 
        SDL_Rect empty_dst_rect{}; 

        SDL_Rect full_src_rect{}; 
        SDL_Rect full_dst_rect{}; 
        SDL_Point center{NULL};

        SDL_Texture *empty_texture;
        SDL_Texture *full_texture;

        // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        SDL_RendererFlip flip = SDL_FLIP_NONE;

    };
    struct Icon {};
    struct Weapon {};

    Health health{}; 

};
