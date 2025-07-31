#pragma once

#include "Renderable.h"
#include <iostream>
#include <SDL2/SDL_mixer.h>

class Musics : public Renderable{
public:
    Musics(bool isMusic, std::string file, int &index);

    std::string file;

    bool play;
    bool isMusic;

    Mix_Music* music;
    Mix_Chunk* chunk;

    int* index;

    void render(SDL_Color* white, bool &game, bool &end);
    virtual Renderable* clone() const;
};