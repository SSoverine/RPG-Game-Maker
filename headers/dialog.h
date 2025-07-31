#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include "Renderable.h"
#include "character.h"

class dialog : public Renderable{
public:
    std::string text;
    std::string background;
    std::string person;
    std::vector<character>* chars;

    TTF_Font* font;
    SDL_Renderer* rend;
    int width;
    int height;

    dialog(std::string text, std::string bg, std::string person, std::vector<character> &chars, SDL_Renderer* r, int w, int h, TTF_Font* font);
    void render(SDL_Color* white, bool &game, bool &end) override;
    Renderable* clone() const;
};