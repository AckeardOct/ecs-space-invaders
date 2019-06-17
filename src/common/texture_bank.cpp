#include "texture_bank.h"
#include <common/logger.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


TextureBank::~TextureBank()
{
    for(auto& pair : textureMap) {
        SDL_DestroyTexture(pair.second.sdl_texture);
    }
    textureMap.clear();
}


const Texture* TextureBank::getTexture(const char *spritePath)
{
    auto iter = textureMap.find(spritePath);
    if (iter == textureMap.end()) {
        // try load texture
        SDL_Surface* surface = IMG_Load(spritePath);
        if (surface == nullptr) {
            LogError("can't load image: %s! SDL_image Error: %s\n", spritePath, IMG_GetError());
            return nullptr;
        }
        SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(&sdl_renderer, surface);
        SDL_FreeSurface(surface);
        if (sdl_texture == nullptr) {
            LogError("can't create texture: %s ! SDL_image Error: %s\n", spritePath, SDL_GetError());
            return nullptr;
        }
        Texture texture;
        texture.sdl_texture = sdl_texture;
        SDL_QueryTexture(sdl_texture, nullptr, nullptr, &texture.sdl_rect.w, &texture.sdl_rect.h);
        textureMap[spritePath] = texture;
        return nullptr;
    }

    return &iter->second;
}
