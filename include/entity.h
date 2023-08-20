#pragma once 

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Entity {
public:
    explicit Entity() = default;
    virtual ~Entity() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}


    virtual SDL_Rect collider() { return m_dst_rect; }

private:
    int m_x = 0;
    int m_y = 0;
    
    double m_angle = 0;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};
    SDL_Point m_center{NULL};

};
