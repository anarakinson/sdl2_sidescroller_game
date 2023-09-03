#pragma once

#include <iostream>
#include <entity.h>


class Camera {
public: 
    Camera() = default;
    ~Camera() = default;
    
    void attach(Entity *owner) {
        m_owner = owner;
    }

    void update() {
        
    }

    void update_position(Vector2D &modifier, double scaler, int margine = 200, int top_border = 350, int bottom_border = 400) {
        /* ----- horizontal ----- */
        int left_border = 0;
        int right_border = 800;
        margine = scaler < 1 ? margine : static_cast<int>(margine / scaler);
        left_border += margine;
        right_border -= margine;
        
        double x_speed_modifier = 1;

        int position_x = static_cast<int>(m_owner->m_position.x * scaler);
        int position_y = static_cast<int>(m_owner->m_position.y * scaler);
        int position_w = static_cast<int>(m_owner->m_position.w * scaler);
        int position_h = static_cast<int>(m_owner->m_position.h * scaler);

        right_border = right_border - position_w;
        
        // std::cout << left_border << " " << right_border << std::endl;
        
        if (
            position_x > right_border || 
            ( m_owner->m_position.right_direction == true && 
            position_x > left_border && position_x > left_border + position_w )
        ) {
            modifier.x -= (m_owner->max_speed() * 2) * x_speed_modifier;
        } 
        else if (
            position_x < left_border || 
            ( m_owner->m_position.right_direction == false && 
            position_x < right_border && position_x < right_border - position_w )
        ) {
            modifier.x += (m_owner->max_speed() * 2) * x_speed_modifier;
        }
        
        /* ----- vertical ----- */
        if (position_y > bottom_border) {
            modifier.y -= (m_owner->max_speed() * 2) * x_speed_modifier;
        } 
        else if (position_y < top_border) {
            modifier.y += (m_owner->max_speed() * 2) * x_speed_modifier;
        }

    }

private: 
    Entity *m_owner; 

};


// class Parent;

// class Child_One;
// class Child_Two;
// class Child_Three;


// class Attacher{
// public:
//     void attach(Parent *object);
//     void report();

// private:
//     Parent *m_owner;
// };

// int main() {
//     std::unique_ptr<Child_One> ch_one{new Child_One{}};
//     std::unique_ptr<Child_Two> ch_two{new Child_One{}};
//     std::unique_ptr<Child_Three> ch_three{new Child_One{}};
    
//     Attacher att{};

//     att.attach(ch_one);

//     ch_one.do_some_important_work();
//     ch_two.do_some_important_work();
//     ch_three.do_some_important_work();
//     att.report();

    
//     att.attach(ch_two);

//     ch_one.do_some_important_work();
//     ch_two.do_some_important_work();
//     ch_three.do_some_important_work();
//     att.report();

    
//     att.attach(ch_three);

//     ch_one.do_some_important_work();
//     ch_two.do_some_important_work();
//     ch_three.do_some_important_work();
//     att.report();

    
// }