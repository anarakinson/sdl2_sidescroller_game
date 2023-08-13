#include <game.h>
#include <player.h>
#include <texture_manager.h>



SDL_Renderer *Game::renderer() { return m_renderer; }
SDL_Renderer *Game::m_renderer = nullptr;

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

        m_renderer = SDL_CreateRenderer(m_window, -1, 0);               // create renderer
        if (m_renderer) {
            SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 100);
            std::cout << "Window rendered" << std::endl;
        }

        m_player = std::unique_ptr<Player>(new Player{0, 0, "assets/packman_set.png"});

        m_running = true;                                         // set game running

    }
    else {
        std::cout << "Something went wrong..." << std::endl;      // if can't initialize
        m_running = false;                                        // set game not running
    }

}


void Game::update() {
    
    // update state
    m_player->update();
    for (auto &entity : m_content) {
        entity->update();
    }

}


void Game::render() {
    SDL_RenderClear(m_renderer);

    // rendering
    m_player->render();
    for (auto &entity : m_content) {
        entity->render();
    }

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
        case SDL_KEYDOWN:
            // std::cout << "key down" << std::endl;
            if (event.key.keysym.sym == SDLK_LEFT) { m_player->move_left(true); }
            else if (event.key.keysym.sym == SDLK_RIGHT) { m_player->move_right(true); }
            if (event.key.keysym.sym == SDLK_UP) { m_player->move_up(true); }
            else if (event.key.keysym.sym == SDLK_DOWN) { m_player->move_down(true); }
            break;
        case SDL_KEYUP:
            // std::cout << "key up" << std::endl; 
            if (event.key.keysym.sym == SDLK_LEFT) { m_player->move_left(false); }
            else if (event.key.keysym.sym == SDLK_RIGHT) { m_player->move_right(false); }
            if (event.key.keysym.sym == SDLK_UP) { m_player->move_up(false); }
            else if (event.key.keysym.sym == SDLK_DOWN) { m_player->move_down(false); }
            break;
        case SDL_KEYDOWN && SDL_KEYUP:
            break;
        default:
            break;
    }
}


