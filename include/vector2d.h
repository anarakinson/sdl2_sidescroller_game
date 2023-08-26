#pragma once 

#include <iostream>


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

    Vector2D operator += (const Vector2D &other) { 
        x += other.x;
        y += other.y;
        return *this; 
    }
    Vector2D operator -= (const Vector2D &other) { 
        x -= other.x;
        y -= other.y;
        return *this; 
    }
    Vector2D operator *= (const Vector2D &other) { 
        x *= other.x;
        y *= other.y;
        return *this; 
    }
    Vector2D operator /= (const Vector2D &other) { 
        x /= other.x;
        y /= other.y;
        return *this; 
    }

    void operator = (int value) { x = value; y = value; }
    bool operator == (int value) { return x == value && y == value; }
};

inline Vector2D operator + (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs; 
}
inline Vector2D operator - (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs; 
}
inline Vector2D operator * (Vector2D lhs, const Vector2D &rhs) { 
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs; 
}
inline Vector2D operator / (Vector2D lhs, const Vector2D &rhs) { 
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
