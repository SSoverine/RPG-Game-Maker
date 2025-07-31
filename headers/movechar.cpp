#include "movechar.h"

movechar::movechar(SDL_Renderer* rend, int ind, float s, int x, int y, int delay,int w, int h, std::string bg,
    std::vector<character> &chars, Renderable &dg, int &index){
    this->rend = rend;
    nScale = s;
    nX = x;
    nY = y;
    this->delay = delay;
    this->ind = ind;
    this->r = r;
    this->index = &index;
    this->width = w;
    this->height = h;
    this->chars = &chars;
    this->dg = &dg;
    this->background = bg;
}

void movechar::render(SDL_Color* white, bool &game, bool &end){
    bool animating = true;
    while(animating){
        SDL_Rect rect;
        rect.x = width/20;
        rect.y = height/2 + height/3.5;
        rect.w = width - width/10;
        rect.h = height/5;

        SDL_Surface* bg = SDL_LoadBMP_RW(SDL_RWFromFile(background.c_str(), "rb"),1);
        SDL_Texture* bgT = SDL_CreateTextureFromSurface(rend, bg);
        SDL_Rect bgR;
        bgR.x = 0;
        bgR.y = 0;
        bgR.w = width;
        bgR.h = height;

        SDL_RenderCopy(rend, bgT, NULL, &bgR);


        if (chars->at(ind).x < nX) chars->at(ind).x += 1;
        else if (chars->at(ind).x > nX) chars->at(ind).x -= 1;
    
        if (chars->at(ind).y < nY) chars->at(ind).y += 1;
        else if (chars->at(ind).y> nY) chars->at(ind).y -= 1;
    
        if (chars->at(ind).scale < nScale) chars->at(ind).scale += 0.01;
        else if (chars->at(ind).scale > nScale)chars->at(ind).scale -= 0.01;

        for(character car : *chars){
            SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromFile(car.file.c_str(), "rb"), 1);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
            SDL_Rect recta = {car.x, car.y, surf->w*car.scale, surf->h*car.scale};
    
            SDL_RenderCopy(rend, texture, NULL, &recta);
    
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(texture);
        }

        SDL_Surface* dbg = SDL_LoadBMP_RW(SDL_RWFromFile("./headers/assets/dAsset.bmp", "rb"),1);
        SDL_Texture* dbgT = SDL_CreateTextureFromSurface(rend, dbg);

        SDL_Surface* pbg = SDL_LoadBMP_RW(SDL_RWFromFile("./headers/assets/dAsset2.bmp", "rb"),1);
        SDL_Texture* pbgT = SDL_CreateTextureFromSurface(rend, pbg);
        SDL_Rect rPerson1 = {rect.x+rect.x/4, rect.y-rect.h/5, pbg->w, pbg->h};

        SDL_RenderCopy(rend,dbgT, NULL, &rect);
        SDL_RenderCopy(rend, pbgT, NULL, &rPerson1);


        SDL_RenderPresent(rend);

        SDL_Delay(delay);

        SDL_RenderClear(rend);

        if (abs(chars->at(ind).x - nX) <= 1 && abs(chars->at(ind).y - nY) <= 1 && abs(chars->at(ind).scale - nScale) <= 1) {
            chars->at(ind).x = nX;
            chars->at(ind).y = nY;
            chars->at(ind).scale = nScale;
            (*index)++;
            animating = false;
        }
    }
}

Renderable* movechar::clone() const {
    return new movechar(*this);
}