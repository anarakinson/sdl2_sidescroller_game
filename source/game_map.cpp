#include <game.h>
#include <game_map.h>
#include <texture_manager.h>

#include <vector>


using namespace level;


void Map::draw_map() {
    
    int tile_type = 0; 
    for (int row = 0; row < m_lvl.height(); ++row) {
        for (int col = 0; col < m_lvl.width(); ++col) {
            tile_type = m_lvl.map()[row][col];

            m_solid->set_x(col * m_solid->get_w());
            m_solid->set_y(row * m_solid->get_h());

            // m_dst_rect.x = col * m_dst_rect.w;
            // m_dst_rect.y = row * m_dst_rect.h;

            switch(tile_type) {
                case 0:                 // 0 - draw nothing
                    break;
                case 1:                 // 1 - draw solid tile
                    // TextureManager::Draw(m_solid, m_scr_rect, m_dst_rect);
                    TextureManager::Draw(m_solid->texture(), m_solid->scr_rect(), m_solid->dst_rect());
                    break;
                default:
                    break;
            }
        }
    }

}