#pragma once
#include <iostream>

class character{
public:
    int x;
    int y;
    float scale;
    std::string file;
    character(int x, int y, float scale, std::string file);
};