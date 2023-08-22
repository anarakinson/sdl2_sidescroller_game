#include <game.h>
#include <player.h>
#include <collision.h>
#include <texture_manager.h>


template <class T>
std::unique_ptr<T> copy_unique(const std::unique_ptr<T> &source) {
    return source ? std::make_unique<T>(*source) : nullptr;
}

// set up entity counter
int Entity::counter = 0;
SDL_Renderer *TextureManager::renderer = nullptr;

void Game::init(const char *title, int x, int y, int w, int h, bool foolscreen) {

    m_x = x; 
    m_y = y; 
    m_w = w;
    m_h = h;

    int params = 0;
    if (foolscreen) {                                                 // set screen mode
        params = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {                         // if sdl initialize
        std::cout << "Initialize subsystem..." << std::endl;   
        m_window = SDL_CreateWindow(title, m_x, m_y, m_w, m_h, params);   // create window
        if (m_window) {
            std::cout << "Window created" << std::endl;
        }

        TextureManager::renderer = SDL_CreateRenderer(m_window, -1, 0);               // create renderer
        if (TextureManager::renderer) {
            SDL_SetRenderDrawColor(TextureManager::renderer, 100, 100, 100, 100);
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
        for (auto &other_entity : m_content) {
            if (
                Collision::is_collide(m_player->collider(), entity->collider()) 
                || (entity->index != other_entity->index &&                     // not compare entity with itself
                    entity->type() != "tile" &&                                 // not compare tiles
                    Collision::is_collide(entity->collider(), other_entity->collider()))
            ) {
                std::cout << "Collision detected for entity " << entity->index << std::endl;
            }
        }
    }

}


void Game::render() {
    SDL_RenderClear(TextureManager::renderer);

    // rendering
    m_player->render();
    for (auto &entity : m_content) {
        entity->render();
    }
    
    SDL_RenderPresent(TextureManager::renderer);
}


void Game::clean() {
    SDL_DestroyWindow(m_window);          // destroy renderer and window
    SDL_DestroyRenderer(TextureManager::renderer);
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
            if (event.key.keysym.sym == SDLK_LEFT) { 
                m_player->move_left(true); 
                m_player->move_right(false); 
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) { 
                m_player->move_right(true); 
                m_player->move_left(false); 
            }
            if (event.key.keysym.sym == SDLK_UP) { 
                m_player->move_up(true); 
                m_player->move_down(false); 
            }
            else if (event.key.keysym.sym == SDLK_DOWN) { 
                m_player->move_down(true); 
                m_player->move_up(false); 
            }
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

