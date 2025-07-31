#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "game.h"
#include "dialog.h"
#include "Renderable.h"
#include "choices.h"
#include "Musics.h"
#include "cutscene.h"
#include "movechar.h"
#include "story.h"
#include <memory>
#include <typeinfo>

SDL_Event ev;
SDL_Color white = {255,255,255,255};

game::game(SDL_Renderer* rend, int width, int height){
    this->rend = rend;
    this->width = width;
    this->height = height;
}

void game::start(bool &game, TTF_Font* font){
    Mix_Chunk* ch = Mix_LoadWAV("./headers/assets/music/sound.mp3");
    int index = 0;

    story st(index, width, height, rend, font);
    SDL_Delay(5000);

    bool dialogEnd = false;
    while(game){
        while(SDL_PollEvent(&ev)){
            if(ev.type == SDL_QUIT){
                game = false;
            }if(ev.type == SDL_KEYUP){
                switch(ev.key.keysym.sym){
                    case SDLK_ESCAPE:
                        game = false;
                        break;
                    case SDLK_SPACE:
                        index++;
                        dialogEnd = false;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderClear(rend);

        st.vec.at(index)->render(&white,game, dialogEnd);
        std::cout<<index;

        SDL_RenderPresent(rend);
        if(typeid(st.vec.at(index-1)) == typeid(Musics)){

        }else{
            SDL_Delay(10);
        }
    }for (Renderable* r : st.vec) delete r;
}