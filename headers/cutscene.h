#pragma once

#include "Renderable.h"
#include <SDL2/SDL_image.h>
#include <iostream>

class cutscene : public Renderable{
public:
    std::string file;
    SDL_Renderer* rend;
    int* index;
    int w;
    int h;

    cutscene(std::string file, SDL_Renderer* rend, int width, int height, int *index);

    void render(SDL_Color* white, bool &game, bool &end);
    Renderable* clone() const;
};