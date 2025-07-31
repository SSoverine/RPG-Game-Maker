#pragma once

#include <iostream>
#include <vector>
#include "dialog.h"
#include "Renderable.h"
#include "choices.h"
#include "Musics.h"
#include "cutscene.h"
#include "movechar.h"

class story{
public:
    int* index;
    std::vector<Renderable*> vec;
    story(int &index, int width, int height, SDL_Renderer* rend, TTF_Font* font);
};