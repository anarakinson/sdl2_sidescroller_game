#pragma once 

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


namespace gameloop {

    class Game {
    public:
        Game() = default;
        ~Game();

        void init(const char *title, int x, int y, int w, int h, bool foolscreen = false);
        void update();
        void render();
        void clean();
        void handle_events();

        bool is_running() { return m_running; }   

        // one renderer for all objects
        static SDL_Renderer *renderer;

    private:
        SDL_Window *m_window;
        bool m_running = false;
        int m_counter = 0;

        int m_x = 0;
        int m_y = 0;
        int m_w = 0;
        int m_h = 0;

    };

} // namespace gameloop

