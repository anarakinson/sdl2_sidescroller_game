#pragma once 

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



class Vector2D {
public:
    int x = 0;
    int y = 0;

    Vector2D operator *= (int modifier) { 
        x *= modifier;
        y *= modifier;
        
        return *this; 
    }
    Vector2D operator /= (int modifier) { 
        x /= modifier;
        y /= modifier;
        
        return *this; 
    }
    Vector2D operator += (int modifier) { 
        x += modifier;
        y += modifier;
        
        return *this; 
    }
    Vector2D operator -= (int modifier) { 
        x -= modifier;
        y -= modifier;
        
        return *this; 
    }

    void operator = (int value) { x = value; y = value; }
    bool operator == (int value) { return x == value && y == value; }
};

Vector2D operator + (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs; 
}
Vector2D operator - (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs; 
}
Vector2D operator * (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs; 
}
Vector2D operator / (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs; 
}

class Position2D {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    Position2D operator += (Vector2D vector) {
        x += vector.x;
        y += vector.y;
        return *this;
    }    
    Position2D operator -= (Vector2D vector) {
        x -= vector.x;
        y -= vector.y;
        return *this;
    }    
    Position2D operator *= (Vector2D vector) {
        x *= vector.x;
        y *= vector.y;
        return *this;
    }    
    Position2D operator /= (Vector2D vector) {
        x /= vector.x;
        y /= vector.y;
        return *this;
    }    

};


class Entity {
public:
    explicit Entity() { index = counter++; };
    virtual ~Entity() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}

    virtual std::string type() { return "basic entity"; }

    bool is_collide() { return m_is_collide; }
    void collide() { m_is_collide = true; }


    virtual SDL_Rect collider() { return m_dst_rect; }

    static int counter;
    int index;

    Vector2D velocity{};
    Position2D m_position{};

protected:
    
    double m_angle = 0;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};
    SDL_Point m_center{NULL};

    bool m_is_collide = false;

};
