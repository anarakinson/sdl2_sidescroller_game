#include <player.h>


void Player::set_animation_frames() {
    /* ----- idle ----- */
    m_src_rect[0].x = 400;        // source image coordinates on tileset 
    m_src_rect[0].y = 720; 
    m_src_rect[0].w = 120;      // source image width and height on tileset 
    m_src_rect[0].h = 160; 

    m_src_rect[1].x = 610;        // source image coordinates on tileset 
    m_src_rect[1].y = 720; 
    m_src_rect[1].w = 120;      // source image width and height on tileset 
    m_src_rect[1].h = 160; 

    m_src_rect[2].x = 820;        // source image coordinates on tileset 
    m_src_rect[2].y = 720; 
    m_src_rect[2].w = 120;      // source image width and height on tileset 
    m_src_rect[2].h = 160; 

    m_src_rect[3].x = 1030;        // source image coordinates on tileset 
    m_src_rect[3].y = 720; 
    m_src_rect[3].w = 120;      // source image width and height on tileset 
    m_src_rect[3].h = 160; 

    /* ----- walk ----- */
    m_src_rect[4].x = 400;        // source image coordinates on tileset 
    m_src_rect[4].y = 930; 
    m_src_rect[4].w = 120;      // source image width and height on tileset 
    m_src_rect[4].h = 160; 

    m_src_rect[5].x = 610;        // source image coordinates on tileset 
    m_src_rect[5].y = 930; 
    m_src_rect[5].w = 120;      // source image width and height on tileset 
    m_src_rect[5].h = 160; 

    m_src_rect[6].x = 820;        // source image coordinates on tileset 
    m_src_rect[6].y = 930; 
    m_src_rect[6].w = 120;      // source image width and height on tileset 
    m_src_rect[6].h = 160; 

    m_src_rect[7].x = 1030;        // source image coordinates on tileset 
    m_src_rect[7].y = 930; 
    m_src_rect[7].w = 120;      // source image width and height on tileset 
    m_src_rect[7].h = 160; 

    m_src_rect[8].x = 1240;        // source image coordinates on tileset 
    m_src_rect[8].y = 930; 
    m_src_rect[8].w = 120;      // source image width and height on tileset 
    m_src_rect[8].h = 160; 

    m_src_rect[9].x = 1450;        // source image coordinates on tileset 
    m_src_rect[9].y = 930; 
    m_src_rect[9].w = 120;      // source image width and height on tileset 
    m_src_rect[9].h = 160; 

    /* ----- shoot ----- */
    m_src_rect[10].x = 400;        // source image coordinates on tileset 
    m_src_rect[10].y = 930; 
    m_src_rect[10].w = 120;      // source image width and height on tileset 
    m_src_rect[10].h = 160; 

    m_src_rect[11].x = 620;        // source image coordinates on tileset 
    m_src_rect[11].y = 930; 
    m_src_rect[11].w = 120;      // source image width and height on tileset 
    m_src_rect[11].h = 160; 

    
}


void Player::update() {

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
    if (m_move_up) { m_input.y = -10; }
    else if (m_move_down) { m_input.y = 1; } 
    // jump
    if (m_jump && m_down_collision) { m_is_jumping = true; }
    if (m_is_jumping && m_jump) { m_input.y = -10; ++jump_counter; }
    if (jump_counter > m_jump_duration || !m_jump || m_up_collision) { m_is_jumping = false; jump_counter = 0; }

    // shoot
    if (shoot_counter >= shoot_cooldown / 2) { m_is_shooting = false; }
    if (m_shoot && shoot_counter > shoot_cooldown) { 
        shoot_counter = 0;
        m_is_shooting = true;
        int speed_modifier = 0;
        if (m_move_left || m_move_right) { speed_modifier = m_max_speed; }
        std::unique_ptr<Projectile> projectile{new Projectile{m_position, m_current_proj_type, speed_modifier, 10}};
        m_projectiles.emplace_back(std::move(projectile)); 
    }

    // apply gravity
    apply_gravity();

    velocity += m_input;
    velocity.y += m_gravity;

    velocity.x = std::max(-m_max_speed, std::min(velocity.x, m_max_speed));
    velocity.y = std::max(-m_max_speed, std::min(velocity.y, m_max_speed));

    // set position
    resolve_collisions();
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

    // update animation frame 
    ++m_current_frame;
    
}


void Player::render() { 
    
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

}
