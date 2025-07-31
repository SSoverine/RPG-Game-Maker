#include "Musics.h"

Musics::Musics(bool isMusic, std::string file, int &index){
    this->isMusic = isMusic;
    this->file = file;
    this->index = &index;
    if(isMusic){
        this->music = Mix_LoadMUS(file.c_str());
    }else{
        this->chunk = Mix_LoadWAV(file.c_str());
    }
    play = true;
}

void Musics::render(SDL_Color* white, bool &game, bool &end){

    if(play){
        if(isMusic){
            Mix_PlayMusic(music, -1);
        }else{
            Mix_PlayChannel(-1, chunk, 0);
            std::cout << "Sa";
        }
        play = false;
    }else{
        if (isMusic) {
            Mix_HaltMusic(); 
            Mix_FreeMusic(music);
        } else {
            Mix_HaltChannel(-1); 
            Mix_FreeChunk(chunk);
        }
        play = true;
    }
    *index += 1;
    std::cout << *index << std::endl << play;
}

Renderable* Musics::clone() const{
    return new Musics(*this);
}