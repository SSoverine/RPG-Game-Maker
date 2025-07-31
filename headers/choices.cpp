#include "choices.h"
#include <SDL2/SDL_mixer.h>

#include <algorithm>

choices::choices(std::vector<std::string> options, 
                std::vector<std::vector<Renderable*>> ways,
                SDL_Renderer* r, int w, int h, TTF_Font* font,
                std::string t, std::string bg, std::string person, 
                std::vector<character> chars, std::vector<Renderable*> &vec, int &index)
    : options(std::move(options)),
      ways(std::move(ways)),
      rend(r),
      width(w),
      height(h),
      font(font),
      text(t),
      background(bg),
      person(person),
      chars(chars),
      oldWay(&vec),
      index(&index)
{

}

choices::~choices() {
    ways.clear();
}
void choices::render(SDL_Color* white, bool &game, bool &end) {
    SDL_Event ev;

    int startY = height/4-(options.size()*40)/2;
    bool selected = true;
    bool deger = false;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    

    Mix_Chunk* click = Mix_LoadWAV("./headers/assets/music/click.mp3");
    Mix_Chunk* hover = Mix_LoadWAV("./headers/assets/music/hover.mp3");
    std::vector<bool> hv;

    for(int i = 0; i<options.size(); ++i){
        hv.push_back(false);
    }
    while(selected){
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

        for(character car : chars){
            SDL_Surface* surf = SDL_LoadBMP_RW(SDL_RWFromFile(car.file.c_str(), "rb"), 1);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surf);
            SDL_Rect recta = {car.x, car.y, surf->w*car.scale, surf->h*car.scale};

            SDL_RenderCopy(rend, texture, NULL, &recta);
        }

        SDL_Rect personBg= {rect.x, rect.y-rect.h/4, rect.w/8, rect.h/5};

        SDL_Surface* Person = TTF_RenderText_Solid(font,person.c_str(), *white);
        SDL_Texture* mPerson = SDL_CreateTextureFromSurface(rend, Person);

        SDL_Surface* pbg = SDL_LoadBMP_RW(SDL_RWFromFile("./headers/assets/dAsset2.bmp", "rb"),1);
        SDL_Texture* pbgT = SDL_CreateTextureFromSurface(rend, pbg);
        SDL_Rect rPerson1 = {rect.x+rect.x/4, rect.y-rect.h/5, pbg->w, pbg->h};
        SDL_Rect rPerson2 = {rect.x+rect.x/3, rect.y-rect.h/5.5, Person->w, Person->h};


        SDL_Surface* message = TTF_RenderText_Solid(font,text.c_str(), *white);
        SDL_Texture* mMessage = SDL_CreateTextureFromSurface(rend, message);
        SDL_Rect rMessage = {rect.x+rect.x/7, rect.y+rect.y/35, message->w, message->h};

        for (size_t i = 0; i < options.size(); ++i) {
            SDL_SetRenderDrawColor(rend, 28, 170, 227, 255);
            //SDL_RenderFillRect(rend, &rect);
            SDL_RenderCopy(rend, dbgT, NULL, &rect);
    
    
            SDL_RenderCopy(rend, pbgT, NULL, &rPerson1);
            SDL_RenderCopy(rend, mPerson, NULL, &rPerson2);
        
    
    
            SDL_RenderCopy(rend, mMessage, NULL, &rMessage);
            
            int x; 
            int y;
    
            SDL_GetMouseState(&x, &y);
    
            while(SDL_PollEvent(&ev)){
                if(ev.type == SDL_KEYDOWN){
                    switch(ev.key.keysym.sym){
                        case SDLK_ESCAPE:
                            game = false;
                            break;
                        case SDLK_SPACE:
                            end = true;
                            break;
                    }
                }if(ev.type == SDL_MOUSEBUTTONUP){
                    deger = true;
                }
            }
            
            SDL_Surface* surf = TTF_RenderText_Solid(font, options[i].c_str(), *white);
            SDL_Texture* text = SDL_CreateTextureFromSurface(rend, surf);
            SDL_Rect textRect = {width/2 - surf->w/2, (startY)+(surf->w*i) + surf->w/10, surf->w, surf->h};
            
            SDL_Rect bg = {width/2-width/10, (startY)+(surf->w*i), width/5, surf->h+surf->h/2 + surf->h/10};

            if(x<bg.x+bg.w && bg.x<x && y<bg.y+bg.h && y>bg.y){
                SDL_SetRenderDrawColor(rend, 9, 71, 127, 255);
                if(!hv[i]){
                    Mix_PlayChannel(-1, hover, 0);
                    hv[i] = true;
                }
                if(deger){
                    Mix_PlayChannel(-1, click, 0);
                    oldWay->clear();
                    for (Renderable* item : ways[i]) {
                        if (item) oldWay->push_back(item->clone());
                    }

                    
                    *index=0;
                    std::cout << "eee\n";
                    selected = false;
                    SDL_SetRenderDrawColor(rend, 00, 00, 00, 255);
                    break;
                }
            }else{
                SDL_SetRenderDrawColor(rend, 28, 170, 227, 255);
                hv[i] = false;
            }



            SDL_RenderFillRect(rend, &bg);
            SDL_RenderCopy(rend, text, NULL, &textRect);
            
            if (surf!=nullptr) {
                SDL_FreeSurface(surf);  
            }

            if (text!=nullptr) {
                SDL_DestroyTexture(text);
            }

        }
        if (bgT != nullptr) {
            SDL_DestroyTexture(bgT);
        }
        
        if (mPerson!=nullptr) {
            SDL_DestroyTexture(mPerson);  
        }
        
        if (mMessage!=nullptr) {
            SDL_DestroyTexture(mMessage);
        }

        SDL_RenderPresent(rend);
        SDL_Delay(10);
        deger = false;
    }
    Mix_FreeChunk(click);
    Mix_CloseAudio();
}

Renderable* choices::clone() const {
    return new choices(*this);
}
