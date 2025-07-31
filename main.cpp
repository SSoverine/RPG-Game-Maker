#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "headers/game.h"

using namespace std;

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    TTF_Font* font = TTF_OpenFont("./headers/Aller.ttf", 34);
    if (!font) {
        cerr << "Font yüklenemedi: " << TTF_GetError() << endl;
        return 1;
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);

    int width = DM.w;
    int height = DM.h;

    SDL_Window* win = SDL_CreateWindow("Oyun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_Event e;

    game gm(rend, width, height);

    bool menu = true;
    bool Game = false;

    SDL_Color pink = {28, 170, 227};
    SDL_Color purple = {9, 71, 127, 255};
    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface* message = TTF_RenderText_Solid(font, "Yeni Oyun", pink);
    SDL_Texture* mBasla = SDL_CreateTextureFromSurface(rend, message);
    SDL_Rect rBasla = {width/20, height/4, message->w, message->h};

    SDL_Surface* messageh = TTF_RenderText_Solid(font, "Yeni Oyun", purple);
    SDL_Texture* mBaslah = SDL_CreateTextureFromSurface(rend, messageh);
    SDL_Rect rBaslah = {width/20, height/4, message->w, message->h};


    SDL_Surface* message1 = TTF_RenderText_Solid(font, "Ayarlar", pink);
    SDL_Texture* mAyarlar = SDL_CreateTextureFromSurface(rend, message1);
    SDL_Rect rAyarlar = {width/20, height/8*3, message1->w, message1->h};

    SDL_Surface* message1h = TTF_RenderText_Solid(font, "Ayarlar", purple);
    SDL_Texture* mAyarlarh = SDL_CreateTextureFromSurface(rend, message1h);
    SDL_Rect rAyarlarh = {width/20, height/8*3, message1->w, message1->h};


    SDL_Surface* message2 = TTF_RenderText_Solid(font, "Cikis", pink);
    SDL_Texture* mCikis = SDL_CreateTextureFromSurface(rend, message2);
    SDL_Rect rCikis = {width/20, height/8*4, message2->w, message2->h};

    SDL_Surface* message2h = TTF_RenderText_Solid(font, "Cikis", purple);
    SDL_Texture* mCikish = SDL_CreateTextureFromSurface(rend, message2h);
    SDL_Rect rCikish = {width/20, height/8*4, message2h->w, message2h->h};

    SDL_Surface* bg = SDL_LoadBMP_RW(SDL_RWFromFile("./headers/assets/background.bmp", "rb"),1);
    SDL_Texture* bgT = SDL_CreateTextureFromSurface(rend, bg);
    SDL_Rect bgR;
    bgR.x = 0;
    bgR.y = 0;
    bgR.w = width;
    bgR.h = height;

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    
    Mix_Music* music = Mix_LoadMUS("./headers/assets/music/menu.mp3");
    Mix_Chunk* click = Mix_LoadWAV("./headers/assets/music/click.mp3");
    Mix_Chunk* hover = Mix_LoadWAV("./headers/assets/music/hover.mp3");

    int x, y;
    bool clicked;
    bool hoveredB = false;
    bool hoveredA = false;
    bool hoveredC = false;

    Mix_PlayMusic(music, -1);
    while(menu){
        clicked = false;
        SDL_GetMouseState(&x, &y);
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                menu = false;
            }else if(e.type == SDL_MOUSEBUTTONDOWN){    
                clicked = true;
            }
        }

        SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        SDL_RenderClear(rend);

        SDL_RenderCopy(rend, bgT, NULL, &bgR);

        if(Game){
            Mix_FreeMusic(music);
        }
        while(Game){
            gm.start(Game, font);
        }

        if(x < (rBasla.x + rBasla.w) && x>rBasla.x && y < (rBasla.y + rBasla.h) && y>rBasla.y ){
            SDL_RenderCopy(rend, mBaslah, NULL, &rBaslah);
            if (!hoveredB) {
                Mix_PlayChannel(-1, hover, 0);
                hoveredB = true;
            }
            if(clicked){Mix_PlayChannel(-1, click, 0); SDL_Delay(1000); Game = true;}
        }else{
            SDL_RenderCopy(rend, mBasla, NULL, &rBasla);
            hoveredB = false;
        }

        if(x < (rAyarlar.x + rAyarlar.w) && x>rAyarlar.x && y < (rAyarlar.y + rAyarlar.h) && y>rAyarlar.y ){
            SDL_RenderCopy(rend, mAyarlarh, NULL, &rAyarlarh);
            if(!hoveredA){
                Mix_PlayChannel(-1, hover, 0);
                hoveredA = true;
            }
            if(clicked){Mix_PlayChannel(-1, click, 0);};
        }else{
            SDL_RenderCopy(rend, mAyarlar, NULL, &rAyarlar);        
            hoveredA = false;
        }

        if(x < (rCikis.x + rCikis.w) && x>rCikis.x && y < (rCikis.y + rCikis.h) && y>rCikis.y ){
            SDL_RenderCopy(rend, mCikish, NULL, &rCikish);
            if(!hoveredC){
                Mix_PlayChannel(-1, hover, 0);
                hoveredC = true;
            }
            if(clicked){
                Mix_PlayChannel(-1, click, 0);
                menu = false;
            }
        }else{
            hoveredC = false;    
            SDL_RenderCopy(rend, mCikis, NULL, &rCikis);
        }

        SDL_RenderPresent(rend);
        SDL_Delay(15);
    }
    Mix_FreeChunk(hover);
    Mix_FreeChunk(click);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyTexture(mBasla);
    SDL_FreeSurface(message);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}