#pragma once 


class UI {
public:


private:

    int m_counter = 0;
    double m_angle = 0;
    
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{}; 
    SDL_Point m_center{NULL};

    SDL_Texture *m_texture;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

};