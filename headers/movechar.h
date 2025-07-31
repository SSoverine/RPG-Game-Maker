#pragma once

#include "Renderable.h"
#include <vector>
#include "character.h"
#include "dialog.h"
#include <SDL2/SDL_ttf.h>

class movechar : public Renderable{
public:
    SDL_Renderer* rend;
    character* c;
    Renderable* r;
    Renderable* dg;

    int width;
    int height;
    TTF_Font* f;

    std::string text;
    std::string background;
    std::string person;
    std::vector<character>* chars;

    int ind;
    float nScale;
    int nX;
    int nY;
    int delay;
    int* index;

    movechar(SDL_Renderer* rend, int ind, float s, int x, int y, int delay,int w, int h, std::string bg,
        std::vector<character> &chars, Renderable &dg, int &index);

    void render(SDL_Color* white, bool &game, bool &end);
    Renderable* clone() const;
};