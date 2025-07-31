#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class game{
private:
    SDL_Renderer* rend;
    int width;
    int height;
public:
    game(SDL_Renderer* rend, int width, int height);
    void start(bool &game, TTF_Font* font);
};