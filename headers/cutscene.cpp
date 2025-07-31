#include "cutscene.h"
#include <gif_lib.h>



cutscene::cutscene(std::string file, SDL_Renderer* rend, int width, int height, int* index){
    this->file = file;
    this->rend = rend;
    this->w = width;
    this->h = height;
    this->index = index;
}

        
void cutscene::render(SDL_Color* white, bool &game, bool &end){
    SDL_Event ev;
    int error;
    GifFileType* gif = DGifOpenFileName(file.c_str(), &error); 
    if (!gif) {
        std::cerr << "GIF dosyası açılamadı! Hata kodu: " << error << std::endl;
        return;
    }
    DGifSlurp(gif);

    int canvasWidth = gif->SWidth;
    int canvasHeight = gif->SHeight;
    
    for (int i = 0; i < gif->ImageCount; ++i) {
        SavedImage* frame = &gif->SavedImages[i];
    
        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, canvasWidth, canvasHeight, 32, SDL_PIXELFORMAT_RGBA32);
        Uint32* pixels = (Uint32*)surface->pixels;
    
        SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
    
        int frameX = frame->ImageDesc.Left;
        int frameY = frame->ImageDesc.Top;
        int frameW = frame->ImageDesc.Width;
        int frameH = frame->ImageDesc.Height;
    
        ColorMapObject* colorMap = frame->ImageDesc.ColorMap ? frame->ImageDesc.ColorMap : gif->SColorMap;
        if (!colorMap) continue;
    
        for (int y = 0; y < frameH; ++y) {
            for (int x = 0; x < frameW; ++x) {
                int frameIndex = y * frameW + x;
                int canvasIndex = (frameY + y) * canvasWidth + (frameX + x);
    
                GifByteType colorIndex = frame->RasterBits[frameIndex];
                GifColorType color = colorMap->Colors[colorIndex];
    
                pixels[canvasIndex] = SDL_MapRGBA(surface->format, color.Red, color.Green, color.Blue, 255);
            }
        }
    
        SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
        SDL_Rect destRect;
        float scaleX = (float)w / gif->SWidth;
        float scaleY = (float)h / gif->SHeight;
        float scale = std::min(scaleX, scaleY);

        destRect.w = gif->SWidth * scale;
        destRect.h = gif->SHeight * scale;
        destRect.x = (w - destRect.w) / 2;
        destRect.y = (h - destRect.h) / 2;

    
        if (!texture) continue;
    
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, texture, NULL, &destRect);
        SDL_RenderPresent(rend);
    
        GraphicsControlBlock gcb;
        int delay = 100;
        if (DGifSavedExtensionToGCB(gif, i, &gcb) == GIF_OK) {
            delay = gcb.DelayTime * 10;
        }

        
        SDL_Delay(delay);
        SDL_DestroyTexture(texture);
    }
    
    
    DGifCloseFile(gif, &error);
    (*index)++;
    return;
}

Renderable* cutscene::clone() const {
    return new cutscene(*this);
}