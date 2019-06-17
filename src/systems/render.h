#pragma once

#include <entt/entity/registry.hpp>

class SDL_Renderer;
class TextureBank;


class IRenderSys
{
public:
    virtual void update(entt::registry &reg, SDL_Renderer& sdl_renderer) = 0;
};


class RectRendSys : public IRenderSys
{
public: // IRenderSys interface
    virtual void update(entt::registry &reg, SDL_Renderer &sdl_renderer) override;
};


class SpriteRendSys : public IRenderSys
{
public:
    SpriteRendSys(TextureBank& textureBank)
        : textureBank(textureBank)
    { }

public: // IRenderSys interface
    virtual void update(entt::registry &reg, SDL_Renderer &sdl_renderer) override;

private:
    TextureBank& textureBank;
};
