#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "dialog.h"

dialog::dialog(std::string text, std::string bg, std::string person, std::vector<character>& chars, SDL_Renderer* r, int w, int h, TTF_Font* font){
    this->text = text;
    this->background = bg;
    this->person = person;
    this->chars = &chars;
    this->rend = r;
    this->width = w;
    this->height = h;
    this->font = font;
}

void dialog::render(SDL_Color* white, bool &game, bool &end){
    SDL_Event ev;
    SDL_Rect rect;
    rect.x = width/20;
    rect.y = height/2 + height/3.5;
    rect.w = width - width/10;
    rect.h = height/5;

    SDL_Surface* dbg = SDL_LoadBMP_RW(SDL_RWFromFile("./headers/assets/dAsset.bmp", "rb"),1);
    SDL_Texture* dbgT = SDL_CreateTextureFromSurface(rend, dbg);

    SDL_Surface* bg = SDL_LoadBMP_RW(SDL_RWFromFile(background.c_str(), "rb"),1);
    SDL_Texture* bgT = SDL_CreateTextureFromSurface(rend, bg);
    SDL_Rect bgR;
    bgR.x = 0;
    bgR.y = 0;
    bgR.w = width;
    bgR.h = height;

    SDL_RenderCopy(rend, bgT, NULL, &bgR);

    for(character car : *chars){
        SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromFile(car.file.c_str(), "rb"), 1);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
        SDL_Rect recta = {car.x, car.y, surf->w*car.scale, surf->h*car.scale};

        SDL_RenderCopy(rend, texture, NULL, &recta);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(texture);
    }

    /*SDL_SetRenderDrawColor(rend, 28, 170, 227, 255);
    SDL_RenderFillRect(rend, &rect);*/
    SDL_RenderCopy(rend,dbgT, NULL, &rect);

    SDL_Rect personBg= {rect.x, rect.y-rect.h/4, rect.w/8, rect.h/5};

    SDL_Surface* Person = TTF_RenderText_Solid(font,person.c_str(), *white);
    SDL_Texture* mPerson = SDL_CreateTextureFromSurface(rend, Person);

    SDL_Surface* pbg = SDL_LoadBMP_RW(SDL_RWFromFile("./headers/assets/dAsset2.bmp", "rb"),1);
    SDL_Texture* pbgT = SDL_CreateTextureFromSurface(rend, pbg);
    SDL_Rect rPerson1 = {rect.x+rect.x/4, rect.y-rect.h/5, pbg->w, pbg->h};
    SDL_Rect rPerson2 = {rect.x+rect.x/3, rect.y-rect.h/5.5, Person->w, Person->h};

    //SDL_RenderFillRect(rend, &personBg);
    SDL_RenderCopy(rend, pbgT, NULL, &rPerson1);
    SDL_RenderCopy(rend, mPerson, NULL, &rPerson2);

    if(!end){
        std::string dialog = "";
        for(int i = 0; i<text.length(); i++){
            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_KEYUP){
                    switch(ev.key.keysym.sym){
                        case SDLK_ESCAPE:
                            game = false;
                            break;
                        case SDLK_SPACE:
                            end = true;
                            break;
                    }
                }
            }
            if(end){
                break;
            }
            dialog += text[i];
            SDL_Surface* message = TTF_RenderText_Solid(font, dialog.c_str(), *white);
            SDL_Texture* mMessage = SDL_CreateTextureFromSurface(rend, message);
            SDL_Rect rMessage = {rect.x+rect.x/7, rect.y+rect.y/35, message->w, message->h};

            SDL_RenderCopy(rend, mMessage, NULL, &rMessage);
            SDL_RenderPresent(rend);
            SDL_Delay(20);
        }
    }else{
        SDL_Surface* message = TTF_RenderText_Solid(font,text.c_str(), *white);
        SDL_Texture* mMessage = SDL_CreateTextureFromSurface(rend, message);
        SDL_Rect rMessage = {rect.x+rect.x/7, rect.y+rect.y/35, message->w, message->h};

        SDL_RenderCopy(rend, mMessage, NULL, &rMessage);
        SDL_FreeSurface(message);
    }
    end = true;
    SDL_FreeSurface(Person);
}

Renderable* dialog::clone() const {
    return new dialog(*this);
}