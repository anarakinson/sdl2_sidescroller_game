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

    void update_position(Vector2D &modifier, int left_border = 200, int right_border = 400, int top_border = 350, int bottom_border = 400) {
        /* ----- horizontal ----- */
        if (
            m_owner->m_position.x > right_border || 
            ( m_owner->m_position.right_direction == true && 
            m_owner->m_position.x > left_border && m_owner->m_position.x > left_border + 20 )
        ) {
            modifier.x -= m_owner->max_speed() + 2;
        } 
        else if (
            m_owner->m_position.x < left_border || 
            ( m_owner->m_position.right_direction == false && 
            m_owner->m_position.x < right_border && m_owner->m_position.x < right_border - 20 )
        ) {
            modifier.x += m_owner->max_speed() + 2;
        }
        
        /* ----- vertical ----- */
        if (m_owner->m_position.y > bottom_border) {
            modifier.y -= m_owner->max_speed() + 2;
        } 
        else if (m_owner->m_position.y < top_border) {
            modifier.y += m_owner->max_speed() + 2;
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