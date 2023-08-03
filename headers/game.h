#pragma once 

#include <iostream>
#include <SDL2/SDL.h>


namespace gameloop {
    
    class Game {
    public:
        Game();
        ~Game();

        void init(const char *title, int x, int y, int w, int h, bool foolscreen);
        void update();
        void render();
        void clean();
        void handle_events();

        bool is_running() { return m_running; }   

    private:
        bool m_running = false;
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

    };

} // namespace gameloop
