#pragma once 

#include <entity.h>
#include <player.h>
#include <collision.h>
#include <statement_manager.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>


class Game {
public:
    Game() {}
    ~Game() { clean(); }

    // initialize game process
    void init(const char *title, int x, int y, int w, int h, bool foolscreen = false);
    void update();
    void render();
    void clean();
    void handle_events();

    void add_entity(std::unique_ptr<Entity> &&entity) noexcept { 
        std::cout << "Entity " << entity->index << " added" << std::endl;
        m_content.emplace_back(std::move(entity)); 
    }
    void add_tile(std::unique_ptr<Entity> &&entity) noexcept { 
        std::cout << "Entity " << entity->index << " added" << std::endl;
        m_tiles.emplace_back(std::move(entity)); 
    }

    bool is_running() { return m_running; } 
    
    int window_height() { return m_h; }   
    int window_width() { return m_w; }


private:
    SDL_Window *m_window;
    
    bool m_running = false;

    int m_x = 0;   // game window parameters
    int m_y = 0;
    int m_w = 0;
    int m_h = 0;

    std::vector<std::unique_ptr<Entity>> m_content{};
    std::vector<std::unique_ptr<Entity>> m_tiles{};
    std::unique_ptr<Player> m_player{nullptr};
    ObjectStatementManager statement_manager{};

    inline void update_with_modifier(const std::unique_ptr<Entity> &entity, int x_modifier);
    inline bool check_entity_position(const std::unique_ptr<Entity> &entity);
    inline void update_position_modifier(int &modifier);
};
