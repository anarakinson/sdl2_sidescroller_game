#pragma once 

#include <entity.h>
#include <texture_manager.h>

#include <iostream>
#include <string>


class EnemyCrab : virtual public Entity {
public:
    EnemyCrab(int x, int y, int w, int h, SDL_Texture *texture) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;

        m_texture = texture;
        m_max_speed = 1;

        m_max_hitpoints = 3;
        m_hitpoints = m_max_hitpoints;
        
        m_src_rect.x = 180;        // source image coordinates on tileset 
        m_src_rect.y = 90; 
        m_src_rect.w = 140;      // source image width and height on tileset 
        m_src_rect.h = 140; 
        
    }
    ~EnemyCrab() { }

    void update() override { 

        if (m_right_collision) { 
            move_right = false; 
            m_counter = 0; 
        }
        else if (m_left_collision) { 
            move_right = true;
            m_counter = 0; 
        }
        if (m_counter >= 800) { 
            move_right = !move_right; 
            m_counter = 0; 
        }
        m_position.right_direction = move_right; 
        m_counter++;

        if (move_right) { velocity.x = m_max_speed; }
        else { velocity.x = -m_max_speed; }

        if (m_is_damaged && m_damaged_counter <= 30) {
            ++m_damaged_counter;
        }
        if (m_damaged_counter > 30) {
            m_is_damaged = false;
            m_damaged_counter = 0;

            m_src_rect.x = 180;        // source image coordinates on tileset 
            m_src_rect.y = 90; 
            m_src_rect.w = 140;      // source image width and height on tileset 
            m_src_rect.h = 140; 
        }

        resolve_collisions();
        apply_gravity();

        velocity.y += m_gravity;
        m_position += velocity;                                      // update position
        update_position();
        reset_collisions();    

        // std::cout << index << " rc- " << m_right_collision << " lc- " << m_left_collision << "move right" << move_right << " counter: " << m_counter << std::endl;

    }
    void render() override { 
        if (!m_position.right_direction) { m_flip = SDL_FLIP_HORIZONTAL; }
        else { m_flip = SDL_FLIP_NONE; }

        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }
    std::string type() override { return "enemy"; }

    virtual void damaged(int damage = 1) override { 
        m_hitpoints -= damage; 

        m_src_rect.x = 0;        // source image coordinates on tileset 
        m_src_rect.y = 90; 
        m_src_rect.w = 140;      // source image width and height on tileset 
        m_src_rect.h = 140; 

        m_is_damaged = true;

    }


private:

    int m_counter = 0;
    bool move_right = true;
    bool m_is_damaged = false;
    int m_damaged_counter = 0;

};
