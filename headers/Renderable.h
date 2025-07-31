#pragma once

#include <SDL2/SDL.h>

class Renderable {
public:
    virtual void render(SDL_Color* white, bool &game, bool &end) = 0;
    virtual Renderable* clone() const = 0;
    virtual ~Renderable() {}
};