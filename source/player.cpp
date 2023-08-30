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

    
}
