#pragma once 

#include <entity.h>
#include <projectile.h>
#include <collision.h>
#include <texture_manager.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>


class Player : public Entity {
public:
    Player(int x, int y, int w, int h, SDL_Texture *texture) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;
        
        m_max_speed = 2;

        m_texture = texture;
        std::cout << "Player character created" << std::endl;
        
        set_animation_frames();
    }
    ~Player() {
        SDL_DestroyTexture(m_texture);
    }

    void init() override {}
    void update() override {

        update_counters();

        if (m_move_down && m_move_right) { m_move_left = false; }              // resolve inconsistent input
        if (m_move_up && m_move_down) { m_move_down = false; }

        if (                                                                   // update direction
            (!m_position.right_direction && m_move_right) || 
            (m_position.right_direction && m_move_left)
        ) { m_position.right_direction = !m_position.right_direction; }
        
        // process input
        m_input = 0;
        if (m_move_left) { m_input.x = -1; }
        else if (m_move_right) { m_input.x = 1; }
        if (m_move_up) { m_input.y = -5; }
        else if (m_move_down) { m_input.y = 1; } 
        // jump
        if (m_jump && m_down_collision) { m_jump_process = true; }
        if (m_jump_process && m_jump) { m_input.y = -10; ++jump_counter; }
        if (jump_counter > m_jump_duration || !m_jump || m_up_collision) { m_jump_process = false; jump_counter = 0; }

        // shoot
        if (shoot_counter >= 50) { m_is_shooting = false; }
        if (m_shoot && shoot_counter > 100) { 
            shoot_counter = 0;
            m_is_shooting = true;
            std::unique_ptr<Projectile> projectile{new Projectile{m_position, m_current_proj, 10}};
            m_projectiles.emplace_back(std::move(projectile)); 
        }

        // apply gravity
        if (m_down_collision) { m_gravity = 0; } 
        else { m_gravity = std::min(++m_gravity, m_max_speed + 2); } 
        
        velocity += m_input;
        velocity.y += m_gravity;

        // resolve collisions
        if (m_up_collision) { velocity.y = velocity.y < 0 ? 0 : velocity.y; }
        if (m_down_collision) { velocity.y = velocity.y > 0 ? 0 : velocity.y; }
        if (m_left_collision) { velocity.x = velocity.x < 0 ? 0 : velocity.x; }
        if (m_right_collision) { velocity.x = velocity.x > 0 ? 0 : velocity.x; }
        
        velocity.x = std::max(-m_max_speed, std::min(velocity.x, m_max_speed));
        velocity.y = std::max(-m_max_speed, std::min(velocity.y, m_max_speed));
    
        // set position
        m_position += velocity;                                      // update position


        if (!m_move_left && !m_move_right) {                         // stop movement when no input
            if (velocity.x < 0) { ++velocity.x; }
            if (velocity.x > 0) { --velocity.x; }
        }
        if (!m_move_up && !m_move_down) {
            if (velocity.y < 0) { ++velocity.y; }
            if (velocity.y > 0) { --velocity.y; }
        }
    
        update_position();
        reset_collisions();  
        
    }
    void render() override { 
        // SDL_RenderCopy(Game::renderer(), m_texture, &m_src_rect, &m_dst_rect);
        if (!m_position.right_direction) { m_flip = SDL_FLIP_HORIZONTAL; }
        else { m_flip = SDL_FLIP_NONE; }
        
        if (m_move_left || m_move_right) {   // walk
            if ((m_current_frame / m_frame_delay_modifier) < 4 || (m_current_frame / m_frame_delay_modifier) >= 9) { m_current_frame = 5 * m_frame_delay_modifier; }
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect[m_current_frame / m_frame_delay_modifier], &m_dst_rect, m_angle, &m_center, m_flip);
        }
        else if (m_is_shooting) {            // shoot
            if ((m_current_frame / m_frame_delay_modifier) < 9 || (m_current_frame / m_frame_delay_modifier) >= 11) { m_current_frame = 10 * m_frame_delay_modifier; }
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect[m_current_frame / m_frame_delay_modifier], &m_dst_rect, m_angle, &m_center, m_flip);
        }
        else {                               // idle
            if ((m_current_frame / m_frame_delay_modifier) < 0 || (m_current_frame / m_frame_delay_modifier) >= 4) { m_current_frame = 0 * m_frame_delay_modifier; }
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect[m_current_frame / m_frame_delay_modifier], &m_dst_rect, m_angle, &m_center, m_flip);
        }

        ++m_current_frame;

    }

    std::string type() override { return "player"; }

    void move_left(bool state) { m_move_left = state; }
    void move_right(bool state) { m_move_right = state; }
    void move_up(bool state) { m_move_up = state; }
    void move_down(bool state) { m_move_down = state; }

    void jump(bool state) { m_jump = state; }

    void shoot(bool state) { m_shoot = state; }
    // std::vector<std::unique_ptr<Projectile>> projectiles() { return m_projectiles; }
    std::vector<std::unique_ptr<Entity>> m_projectiles{};
    void projectile_explode() { m_projectiles.pop_back(); }

    void update_counters() {
        ++shoot_counter;
    }

    void set_animation_frames();


private:

    // move
    bool m_move_left = false;
    bool m_move_right = false;
    bool m_move_up = false;
    bool m_move_down = false;

    // jump
    bool m_jump = false;
    bool m_jump_process = false;
    int jump_counter = 0;
    int m_jump_duration = 60;

    // shoot
    bool m_shoot = false;
    bool m_is_shooting = false;
    int shoot_counter = 0;
    ProjectileType m_current_proj = ProjectileType::bubble;
    // std::vector<std::unique_ptr<Projectile>> m_projectiles{};

    int m_max_hitpoints = 5;
    int m_hitpoints = m_max_hitpoints;

    int m_gravity = 0;

    Vector2D m_input{};

    SDL_Rect m_src_rect[12];
    int m_current_frame = 0;
    int m_frame_delay_modifier = 6;

};
