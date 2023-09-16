#pragma once 

#include <vector2d.h>
#include <texture_manager.h>

#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>


namespace menu {
    
    class Button {
    public:
        Button(int x, int y, int w, int h, SDL_Texture *texture) {
            // set texture
            m_src_rect.x = x; 
            m_src_rect.y = y; 
            m_src_rect.w = w;
            m_src_rect.h = h; 
            
            m_texture = texture;
        }
        ~Button() = default;

        void set_size(int w, int h) {
            m_dst_rect.w = w;
            m_dst_rect.h = h; 
        }
        void set_position(int x, int y) {
            m_dst_rect.x = x; 
            m_dst_rect.y = y; 
        }

        SDL_Texture *texture() { return m_texture; }
        SDL_Rect src_rect() { return m_src_rect; }
        SDL_Rect dst_rect() { return m_dst_rect; }
        SDL_Point center() { return m_center; }
        double angle() { return m_angle; }

        void render() {
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
        }


    private:

        double m_angle = 0;
        double m_scale = 1;

        // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        SDL_RendererFlip m_flip = SDL_FLIP_NONE;

        SDL_Texture *m_texture;
        SDL_Rect m_src_rect{}; 
        SDL_Rect m_dst_rect{};
        SDL_Point m_center{NULL};

        Position2D m_position{};

        bool m_is_selected = false;

    };


    class Menu {
    public:

        Menu() { 
            m_menu_texture = TextureManager::LoadTexture("assets/UI/menu.png");
        }
        ~Menu() { }

        Menu &operator = (Menu &other) {
            if (this == &other)
                return *this;
            return other;
        }
        
        void init();
        void update();
        void render();

        void set_start_btn(std::unique_ptr<Button> start, int x, int y, int w, int h) {
            // std::unique_ptr<Button> start{ new Button{100, 260, 180, 40, m_menu_texture} };
            // std::unique_ptr<Button> start{ new menu::Button{40, 360, 180, 40, m_menu_texture} };

            start_button = std::move(start);
            start_button->set_position(x, y);
            start_button->set_size(w, h);
        }
        void set_exit_btn(std::unique_ptr<Button> &&button, int x, int y, int w, int h) {
            exit_button = std::move(button);
            exit_button->set_position(x, y);
            exit_button->set_size(w, h);
        }
        void set_resume_btn(std::unique_ptr<Button> &&button, int x, int y, int w, int h) {
            resume_button = std::move(button);
            resume_button->set_position(x, y);
            resume_button->set_size(w, h);
        }

    private:

        SDL_Texture *m_menu_texture;

        std::unique_ptr<Button> start_button;
        std::unique_ptr<Button> resume_button;
        std::unique_ptr<Button> exit_button;

    };


} // namespace menu

