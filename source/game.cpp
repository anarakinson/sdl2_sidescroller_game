#include <game.h>


#include <iostream>
#include <SDL2/SDL.h>


using namespace gameloop;


Game::Game() {
    
}


Game::~Game() {
    clean();
}



void Game::init(const char *title, int x, int y, int w, int h, bool foolscreen){

    int params = 0;
    if (foolscreen) {                                             // set screen mode
        params = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {                     // if sdl initialize
        std::cout << "Initialize subsystem..." << std::endl;   
        m_window = SDL_CreateWindow(title, x, y, w, h, params);   // create window
        if (m_window) {
            std::cout << "Window created" << std::endl;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, 0);               // create renderer
        if (m_renderer) {
            SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 100);
            std::cout << "Window rendered" << std::endl;
        }

        m_running = true;                                         // set game running
    }
    else {
        std::cout << "Something went wrong..." << std::endl;      // if can't initialize
        m_running = false;                                        // set game not running
    }

}

void Game::update() {

}


void Game::render() {
    SDL_RenderClear(m_renderer);

    // rendering

    SDL_RenderPresent(m_renderer);
}


void Game::clean() {
    SDL_DestroyWindow(m_window);          // destroy renderer and window
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();

    std::cout << "Quit the game" << std::endl;
}


void Game::handle_events() {
    SDL_Event event;                       // create empty event
    SDL_PollEvent(&event);                 // handle event
    switch (event.type) {   
        case SDL_QUIT:                     // if event is quit - end game
            m_running = false;
            break;
        default:
            break;
    }
}



