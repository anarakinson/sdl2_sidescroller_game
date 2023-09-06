#include <game.h>



// set up entity counter
int Entity::counter = 0;
SDL_Renderer *TextureManager::renderer = nullptr;

// set static textures
SDL_Texture *ProjectileTexture::projectile_bubble_texture = nullptr;


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
        std::cout << "Initialize subsystems..." << std::endl;   
        
        m_window = SDL_CreateWindow(title, m_x, m_y, m_w, m_h, params);   // create window
        if (m_window) {
            std::cout << "Window created" << std::endl;
        }

        TextureManager::renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );               // create renderer
        if (TextureManager::renderer) {
            SDL_SetRenderDrawColor(TextureManager::renderer, 100, 100, 100, 100);
            std::cout << "Window rendered" << std::endl;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0) {
            std::cout << "Audio start" << std::endl;
        }

        m_ui = std::unique_ptr<UI>(new UI{});

        // add static textures
        ProjectileTexture::load_textures();

        m_running = true;                                         // set game running

    }
    else {
        std::cout << "Something went wrong..." << std::endl;      // if can't initialize
        m_running = false;                                        // set game not running
    }

}


void Game::update() {
    // update state

    // modifier for move environment 
    Vector2D modifier{};
    m_camera.update_position(modifier, m_scale);
    // m_camera.update_position(modifier, (m_w / 3), (m_w / 3) * 2 - m_player->m_position.w, (m_h / 3), (m_h / 3) * 2 - m_player->m_position.h);

    // update background
    int layer_counter = 0;
    int layer_depth = m_background.size() + 2;
    for (auto &layer : m_background) {
        ++layer_counter;
        layer->set_scale(m_scale);     
        layer->update();
        layer->m_position.x += (modifier.x / (layer_depth - layer_counter));
    }

    // update player
    m_player->set_scale(m_scale);
    m_player->update();    
    m_player->m_position += modifier;

    // projectiles
    for (int i = 0; i < m_player->m_projectiles.size(); ++i) {
        auto &projectile = m_player->m_projectiles[i];
        bool explode = false;
        projectile->set_scale(m_scale);    
        projectile->m_position += modifier;
        projectile->update();
        if (projectile->over_range()) { explode = true; }
        for (auto &tile : m_tiles) {
            if (Collision::is_collide(projectile->collider(), tile->collider())) { explode = true; }
        }
        for (int j = 0; j < m_content.size(); ++j) {
            auto &entity = m_content[j];
            if (Collision::is_collide(projectile->collider(), entity->collider())) { 
                explode = true; 
                entity->collide(projectile->collider()); 
            }
        }
        if (explode) { m_player->projectile_explode(i); }

    }
    
    // collisions for entities
    for (int i = 0; i < m_content.size(); ++i) {
        auto &entity = m_content[i];

        entity->set_scale(m_scale);     
        update_and_collide(entity, modifier);
        
        for (int j = i + 1; j < m_content.size(); ++j) {
            auto &other_entity = m_content[j];
            if (
                entity->index != other_entity->index &&                     // not compare entity with itself
                entity->type() != "tile" &&                                 // not compare tiles
                Collision::is_collide(entity->collider(), other_entity->collider())
            ) { 
                entity->collide(other_entity->collider()); 
                other_entity->collide(entity->collider()); 
            }
        }
        for (auto &tile : m_tiles) {
            if (Collision::is_collide(entity->collider(), tile->collider())) { entity->collide(tile->collider()); }
        }
    }
    // collision for tiles
    for (auto &entity : m_tiles) {
        entity->set_scale(m_scale);
        update_and_collide(entity, modifier);
    }

    m_ui->update();

}


void Game::render() {
    SDL_RenderClear(TextureManager::renderer);

    /* ------ rendering ------ */
    //
    for (auto &layer : m_background) {
        layer->render();
    }
    //player
    m_player->render();
    
    // players projectiles
    for (auto &projectile : m_player->m_projectiles) {
        projectile->render();
    }
    // Entities
    for (auto &entity : m_content) {
        if (check_entity_position(entity)) { entity->render(); }
    }
    // Tiles
    for (auto &entity : m_tiles) {
        if (check_entity_position(entity)) { entity->render(); }
    }

    m_ui->render();
    
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
            if (event.key.keysym.sym == SDLK_z) { 
                m_player->jump(true); 
            }
            if (event.key.keysym.sym == SDLK_x) { 
                m_player->shoot(true); 
            }
            if (event.key.keysym.sym == SDLK_q) { 
                m_camera.attach(m_content[1].get());
            }
            if (event.key.keysym.sym == SDLK_w) { 
                if (m_scale < 1.8) m_scale += 0.01;
            }
            if (event.key.keysym.sym == SDLK_e) { 
                if (m_scale > 0.2) m_scale -= 0.01;
            }
            if (event.key.keysym.sym == SDLK_ESCAPE) { 
                m_paused = !m_paused;
            }
            break;
        case SDL_KEYUP:
            // std::cout << "key up" << std::endl; 
            if (event.key.keysym.sym == SDLK_LEFT) { m_player->move_left(false); }
            else if (event.key.keysym.sym == SDLK_RIGHT) { m_player->move_right(false); }
            if (event.key.keysym.sym == SDLK_UP) { m_player->move_up(false); }
            else if (event.key.keysym.sym == SDLK_DOWN) { m_player->move_down(false); }
            if (event.key.keysym.sym == SDLK_z) { m_player->jump(false); }
            if (event.key.keysym.sym == SDLK_x) { m_player->shoot(false); }
            if (event.key.keysym.sym == SDLK_q) { 
                m_camera.attach(m_player.get());
            }
            break;
        case SDL_KEYDOWN && SDL_KEYUP:
            break;
        default:
            break;
    }

}


// check that entity inside game window
bool Game::check_entity_position(const std::unique_ptr<Entity> &entity) {
    return (
        (entity->m_position.x + entity->m_position.w) / m_scale > 0 && entity->m_position.x < m_w / m_scale &&
        (entity->m_position.y + entity->m_position.h) / m_scale > 0 && entity->m_position.y < m_h / m_scale
    );
}

// update and collide
void Game::update_and_collide(const std::unique_ptr<Entity> &entity, Vector2D modifier) {
    entity->update();
    entity->m_position += modifier;  
    if (
        m_player->index != entity->index && 
        Collision::is_collide(m_player->collider(), entity->collider())
    ) {
        entity->collide(m_player->collider());
        m_player->collide(entity->collider());
        if (entity->type() == "enemy") { m_player->hitted(); }
        // std::cout << entity->index << " ";
        // m_player->print_data();
    }
}
