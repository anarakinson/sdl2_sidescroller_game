#include <camera.h>


void Camera::update_position(Vector2D &modifier, double scaler, int margine, int top_border, int bottom_border) {
    /* ----- horizontal ----- */
    int left_border = 0;
    int right_border = 800;
    margine = scaler < 1 ? margine : static_cast<int>(margine / scaler);
    left_border += margine;
    right_border -= margine;
    

    double position_x = static_cast<double>(m_owner->m_position.x * scaler);
    double position_y = static_cast<double>(m_owner->m_position.y * scaler);
    double position_w = static_cast<double>(m_owner->m_position.w * scaler);
    double position_h = static_cast<double>(m_owner->m_position.h * scaler);

    right_border = right_border - position_w;
    
    // std::cout << left_border << " " << right_border << std::endl;
    
    if (
        position_x > right_border || 
        ( m_owner->m_position.right_direction == true && position_x > left_border + position_w )
    ) {

        modifier.x -= (x_speed_modifier - m_owner->max_speed());
    } 
    else if (
        position_x < left_border || 
        ( m_owner->m_position.right_direction == false && position_x < right_border - position_w )
    ) {
        
        modifier.x += (x_speed_modifier - m_owner->max_speed());
    }
    
    /* ----- vertical ----- */
    if (position_y > bottom_border) {
        modifier.y -= (y_speed_modifier - m_owner->max_speed());
    } 
    else if (position_y < top_border) {
        modifier.y += (y_speed_modifier - m_owner->max_speed());
    }

    if (x_speed_modifier > 15) { x_speed_modifier = 15; }
    if (y_speed_modifier > 15) { y_speed_modifier = 15; }
    
    if (
        (position_x > right_border || ( m_owner->m_position.right_direction == true && position_x > left_border + position_w )) || 
        (position_x < left_border || ( m_owner->m_position.right_direction == false && position_x < right_border - position_w )) || 
        x_speed_modifier < 0
    ) { x_speed_modifier += 1; }
    else if (x_speed_modifier > 0) { x_speed_modifier -= 1; }
    if (
        (position_y > bottom_border) || (position_y < top_border) || y_speed_modifier < 0
    ) { y_speed_modifier += 1; }
    else if (y_speed_modifier > 0) { y_speed_modifier -= 1; }

    // std::cout << "x: " << position_x << " y: " << position_y << " " << x_speed_modifier << std::endl;

}