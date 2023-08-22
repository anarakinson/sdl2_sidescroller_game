#pragma once 

#include <game.h>

#include <iostream>
#include <vector>


class Position2D {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
};

class ObjectStatementManager {
public:
    

private:
    std::vector<Position2D> m_positions{};
};