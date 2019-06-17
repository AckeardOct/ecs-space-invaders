#pragma once

#include <unordered_map>

#include <SDL2/SDL_rect.h>

class SDL_Texture;
class SDL_Renderer;
class TextureBank;

class Texture
{
public:
    SDL_Texture* sdl_texture {nullptr};
    SDL_Rect     sdl_rect    {0};
};


class TextureBank
{
public:
    TextureBank(SDL_Renderer& sdl_renderer)
        : sdl_renderer(sdl_renderer)
    { }

    ~TextureBank();

    const Texture* getTexture(const char* spritePath);

private:
    SDL_Renderer& sdl_renderer;
    std::unordered_map<const char*, Texture> textureMap;
};
