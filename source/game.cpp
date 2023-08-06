#include <game.h>
#include <texture_manager.h>
#include <game_object.h>
#include <game_map.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


using namespace gameloop;


GameObject *player;
GameObject *player2;

Map *map;

// one renderer for all objects
SDL_Renderer *Game::renderer = nullptr;


// try create random level
Level lvl1{{
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}};



Game::~Game() {
    clean();
}



void Game::init(const char *title, int x, int y, int w, int h, bool foolscreen) {

    m_x = x; 
    m_y = y; 
    m_w = w;
    m_h = h;

    int params = 0;
    if (foolscreen) {                                             // set screen mode
        params = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {                     // if sdl initialize
        std::cout << "Initialize subsystem..." << std::endl;   
        m_window = SDL_CreateWindow(title, m_x, m_y, m_w, m_h, params);   // create window
        if (m_window) {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(m_window, -1, 0);               // create renderer
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
            std::cout << "Window rendered" << std::endl;
        }

        m_running = true;                                         // set game running
    }
    else {
        std::cout << "Something went wrong..." << std::endl;      // if can't initialize
        m_running = false;                                        // set game not running
    }

    player = new GameObject("assets/packman_set.png", 0, 0);
    player2 = new GameObject("assets/packman_set.png", 25, 25);
    map = new Map(lvl1);

}

void Game::update() {
    
    player->update();
    player2->update();
    
}


void Game::render() {
    SDL_RenderClear(renderer);

    // rendering
    map->draw_map();
    player->render();
    player2->render();

    SDL_RenderPresent(renderer);
}


void Game::clean() {
    SDL_DestroyWindow(m_window);          // destroy renderer and window
    SDL_DestroyRenderer(renderer);
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



