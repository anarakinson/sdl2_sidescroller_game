#pragma once

#include <entity.h>

#include <iostream>


class Camera {
public: 
    Camera() = default;
    ~Camera() = default;
    
    void attach(Entity *owner) {
        m_owner = owner;
    }

    void update() {
        
    }

    void update_position(Vector2D &modifier, double scaler, int margine = 200, int top_border = 350, int bottom_border = 400);

private: 
    Entity *m_owner; 

    int counter = 0;

    double x_speed_modifier = 1;
    double y_speed_modifier = 1;

};

