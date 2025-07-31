#pragma once
#include "Renderable.h"
#include "character.h"
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <memory>

class choices : public Renderable {
public:
    Renderable* clone() const;

    choices(std::vector<std::string> options, 
           std::vector<std::vector<Renderable*>> ways,
           SDL_Renderer* r, int w, int h, TTF_Font* font,
            std::string t, std::string bg, std::string person, 
            std::vector<character> chars, std::vector<Renderable*> &vec, int &index);
    
    void render(SDL_Color* white, bool &game, bool &end) override;
    
    std::vector<std::string> options;
    std::vector<std::vector<Renderable*>> ways;
    
    SDL_Renderer* rend;
    int width;
    int height;
    TTF_Font* font;
    
    int selectedOption = -1;

    std::string text;
    std::string background;
    std::string person;
    std::vector<character> chars;

    std::vector<Renderable*> *oldWay;
    int* index;
    ~choices();
};