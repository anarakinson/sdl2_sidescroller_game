#pragma once 

#include <entity.h>
#include <projectile.h>
#include <collision.h>
#include <texture_manager.h>

#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

extern int UOF;


class Player : public Entity {
public:
    Player(int x, int y, int w, int h, SDL_Texture *texture) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;
        
        m_max_speed = 4;    
        m_max_hitpoints = 5;
        m_hitpoints = m_max_hitpoints;
        
        m_texture = texture;
        std::cout << "Player character created" << std::endl;
        
        set_animation_frames();
    }
    ~Player() { 
        
    }

    void update() override;
    void render() override;

    std::string type() override { return "player"; }

    void move_left(bool state) { m_move_left = state; }
    void move_right(bool state) { m_move_right = state; }
    void move_up(bool state) { m_move_up = state; }
    void move_down(bool state) { m_move_down = state; }

    void jump(bool state) { m_jump = state; }

    void shoot(bool state) { m_shoot = state; }
    // std::vector<std::unique_ptr<Projectile>> projectiles() { return m_projectiles; }
    std::vector<std::unique_ptr<Projectile>> m_projectiles{};
    void projectile_explode(int idx) { m_projectiles.erase(m_projectiles.begin() + idx); }

    void update_counters() {
        ++shoot_counter;
        ++invulnerable_counter;
        if (shoot_counter > 200000000) { shoot_counter = 500; }
        if (invulnerable_counter > 200000000) { invulnerable_counter = 500; }
    }

    int hitpoints() { return m_hitpoints; }
    int max_hitpoints() { return m_max_hitpoints; }
    void hitted() {
        if (invulnerable_counter > 50) { 
            --m_hitpoints; 
            invulnerable_counter = 0;
        }
    }

    ProjectileType current_projectile_type() { return m_current_proj_type; }

    void set_animation_frames();


private:

    // move
    bool m_move_left = false;
    bool m_move_right = false;
    bool m_move_up = false;
    bool m_move_down = false;

    // jump
    bool m_jump = false;
    bool m_is_jumping = false;
    int jump_counter = 0;
    int m_jump_duration = 40;

    // shoot
    bool m_shoot = false;
    bool m_is_shooting = false;
    int shoot_counter = 0;
    int shoot_cooldown = 50;
    ProjectileType m_current_proj_type = ProjectileType::bubble;
    // std::vector<std::unique_ptr<Projectile>> m_projectiles{};

    Vector2D m_input{};

    SDL_Rect m_src_rect[12];
    int m_current_frame = 0;
    int m_frame_delay_modifier = 6 * UOF;

};
