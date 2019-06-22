#include "render.h"
#include <common/utils.h>
#include <components/basic.h>
#include <components/render.h>
#include <common/texture_bank.h>

#include <SDL2/SDL_render.h>

void RectRendSys::update(entt::registry &reg, SDL_Renderer &sdl_renderer)
{
    SDL_Rect rect;
    auto view = reg.view<PositionCmp, RectRendCmp>();
    for (auto ent : view) {
        auto& posCmp  = view.get<PositionCmp>(ent);
        auto& rectCmp = view.get<RectRendCmp>(ent);

        rect.w = (int)posCmp.size.x;
        rect.h = (int)posCmp.size.y;
        rect.x = (int)posCmp.pos.x - rect.w / 2;
        rect.y = (int)posCmp.pos.y - rect.h / 2;

        { // fill
            const glm::ivec4& color = rectCmp.fillColor;
            SDL_SetRenderDrawColor(&sdl_renderer, (u_char)color.r, (u_char)color.g, (u_char)color.b, (u_char)color.a);
            SDL_RenderFillRect(&sdl_renderer, &rect);
        }

        { // border
            const glm::ivec4& color = rectCmp.borderColor;
            SDL_SetRenderDrawColor(&sdl_renderer, (u_char)color.r, (u_char)color.g, (u_char)color.b, (u_char)color.a);
            SDL_RenderDrawRect(&sdl_renderer, &rect);
        }
    }
}


void SpriteRendSys::update(entt::registry &reg, SDL_Renderer &sdl_renderer)
{
    SDL_Rect rect;
    auto view = reg.view<PositionCmp, SpriteRendCmp>();
    for (auto ent : view) {
        auto& posCmp  = view.get<PositionCmp>(ent);
        auto& spriteCmp = view.get<SpriteRendCmp>(ent);

        rect.w = (int)(posCmp.size.x * spriteCmp.scale.x);
        rect.h = (int)(posCmp.size.y * spriteCmp.scale.y);
        rect.x = (int)posCmp.pos.x - rect.w / 2;
        rect.y = (int)posCmp.pos.y - rect.h / 2;

        float angle_rad = Ut::toAngle(posCmp.direction);
        float angle_deg = Ut::toDeg(angle_rad);

        const Texture* texture = textureBank.getTexture(spriteCmp.spritePath);
        if (texture) {
            //SDL_RenderCopy(&sdl_renderer, texture->sdl_texture, &texture->sdl_rect, &rect);
            SDL_RenderCopyEx(&sdl_renderer, texture->sdl_texture, &texture->sdl_rect, &rect, angle_deg, nullptr, SDL_FLIP_NONE);
        }
    }
}
