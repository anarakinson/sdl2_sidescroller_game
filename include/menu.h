#pragma once 

#include <vector2d.h>
#include <texture_manager.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <memory>


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

        int get_x() { return m_dst_rect.x; }
        int get_y() { return m_dst_rect.y; }

        void render() {
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
        }

        std::pair<int, int> get_position() {
            return std::pair<int, int>{m_dst_rect.x, m_dst_rect.y}; 
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


    class Arrow {  
    public:
        Arrow(int x, int y, int w, int h, SDL_Texture *texture) {
            // set texture
            m_src_rect.x = x; 
            m_src_rect.y = y; 
            m_src_rect.w = w;
            m_src_rect.h = h; 
            
            m_texture = texture;
        }
        ~Arrow() = default;

        void set_size(int w, int h) {
            m_dst_rect.w = w;
            m_dst_rect.h = h; 
        }
        void set_position(int x, int y) {
            m_dst_rect.x = x; 
            m_dst_rect.y = y; 
        }
        std::pair<int, int> get_position() {
            return std::pair<int, int>{m_dst_rect.x, m_dst_rect.y}; 
        }
        int get_x() { return m_dst_rect.x; }
        int get_y() { return m_dst_rect.y; }

        void update() {

        }

        void render() {
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
        }

        void down() {
            ++m_choise;
            if (m_choise > 2) { m_choise = 0; }
        }
        void up() {
            --m_choise;
            if (m_choise < 0) { m_choise = 2; }
        }
        int choise() { return m_choise; }
        void choise(int choise) { m_choise = choise; }

    private:

        int m_choise = 0;

        double m_angle = 0;
        double m_scale = 1;

        // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        SDL_RendererFlip m_flip = SDL_FLIP_NONE;

        SDL_Texture *m_texture;
        SDL_Rect m_src_rect{}; 
        SDL_Rect m_dst_rect{};
        SDL_Point m_center{NULL};
    
    };


    class Menu {
    public:

        Menu() { }
        ~Menu() { }

        Menu &operator = (Menu &other) {
            if (this == &other)
                return *this;
            return other;
        }
        
        void init();
        void update();
        void render();

        void set_start_btn(std::unique_ptr<Button> &&start, int x, int y, int w, int h) {
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
        void set_arrow(std::unique_ptr<Arrow> &&arr, int w, int h) {
            arrow = std::move(arr);

            int x = start_button->get_x() - 150;
            int y = start_button->get_y();
            arrow->set_position(x, y);
            arrow->set_size(w, h);
        }

        void arrow_up() {
            arrow->up();
            move_arrow();
        }
        void arrow_down() {
            arrow->down();
            move_arrow();
        }
        void move_arrow() {
            int x, y;
            switch (arrow->choise()) {
            case 0:
                x = arrow->get_x();
                y = start_button->get_y();
                arrow->set_position(x, y);
                break;
            case 1:
                x = arrow->get_x();
                y = resume_button->get_y();
                arrow->set_position(x, y);
                break;
            case 2:
                x = arrow->get_x();
                y = exit_button->get_y();
                arrow->set_position(x, y);
                break;
            default:
                break;
            }
        }
        int arrow_choise() { return arrow->choise(); }
        

    private:

        std::unique_ptr<Button> start_button;
        std::unique_ptr<Button> resume_button;
        std::unique_ptr<Button> exit_button;
        std::unique_ptr<Arrow> arrow;

    };


} // namespace menu

