#pragma once 

#include <iostream>


class Vector2D {
public:
    Vector2D() {}
    Vector2D(int x, int y) { x = x; y = y; }

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

inline Vector2D operator + (Vector2D lhs, int rhs) { 
    lhs.x += rhs;
    lhs.y += rhs;
    return lhs; 
}
inline Vector2D operator - (Vector2D lhs, int rhs) { 
    lhs.x -= rhs;
    lhs.y -= rhs;
    return lhs; 
}
inline Vector2D operator * (Vector2D lhs, int rhs) { 
    lhs.x *= rhs;
    lhs.y *= rhs;
    return lhs; 
}
inline Vector2D operator / (Vector2D lhs, int rhs) { 
    lhs.x /= rhs;
    lhs.y /= rhs;
    return lhs; 
}



class Position2D {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    bool right_direction = true;
    bool left_direction = false;
    bool top_direction = false;
    bool bottom_direction = false;

    struct Center {
        Center(int left, int top, int right, int bottom) {
            x = left + right / 2;
            y = top + bottom / 2;
            
        }

        int x;
        int y;
    };

    Center center() const { return Center{x, y, w, h}; }

    int left_side() const { return x; }
    int right_side() const { return x + w; }
    int up_side() const { return y; }
    int down_side() const { return y + h; }

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


inline Position2D operator + (Position2D lhs, const Vector2D &rhs) {
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    return lhs;
}    
inline Position2D operator - (Position2D lhs, const Vector2D &rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
    return lhs;
}    
inline Position2D operator * (Position2D lhs, const Vector2D &rhs) {
    lhs.x *= rhs.x;
    lhs.y *= rhs.y;
    return lhs;
}    
inline Position2D operator / (Position2D lhs, const Vector2D &rhs) {
    lhs.x /= rhs.x;
    lhs.y /= rhs.y;
    return lhs;
}    