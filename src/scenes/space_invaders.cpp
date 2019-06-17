#include "space_invaders.h"
#include <components/basic.h>
#include <components/render.h>
#include <systems/basic.h>
#include <systems/render.h>

SpaceInvaders::SpaceInvaders(GameWindow &window)
    : IScene(window)
{
    initEntities();
    initBasicSystems();
    initRenderSystems();
}


void SpaceInvaders::input(float dt, const SDL_Event &event)
{
    if (inputSystem) {
        inputSystem->onInput(event);
    }
}


void SpaceInvaders::update(float dt)
{
    for (auto sys : basicSystems) {
        sys->update(reg, dt);
    }
}


void SpaceInvaders::render(float dt)
{
    SDL_Renderer& sdl_renderer = window.getRenderer();
    for (auto sys : renderSystems) {
        sys->update(reg, sdl_renderer);
    }
}


void SpaceInvaders::initBasicSystems()
{    
    inputSystem = new InputSys();
    basicSystems.push_back(inputSystem);
    basicSystems.push_back(new CollisionSys());
}


void SpaceInvaders::initRenderSystems()
{
    renderSystems.push_back(new RectRendSys());
    renderSystems.push_back(new SpriteRendSys(window.getTextureBank()));
}


void SpaceInvaders::initEntities()
{
    glm::vec2 winSize = window.getSize();
    glm::vec2 winCenter = winSize / 2.f;

    { // defender
        glm::vec2 size(50, 50);
        glm::vec2 speed(150, 150);
        glm::vec2 pos = winCenter;
        glm::ivec4 borderColor(255, 0, 0, 255);
        auto spritePath = "resources/images/pixel_ship.png";
        auto entity = reg.create();
        reg.assign<PositionCmp>(entity, pos, size);
        reg.assign<RectRendCmp>(entity, borderColor);
        reg.assign<SpriteRendCmp>(entity, spritePath);
        reg.assign<MoveCmp>(entity, speed);
        reg.assign<ShiftCollisionCmp>(entity);
    }

    // borders
    {
        // left
        glm::vec2 size(1, winSize.y);
        glm::vec2 pos(0, winCenter.y);
        glm::ivec4 borderColor(255, 0, 0, 255);
        auto entity = reg.create();
        reg.assign<PositionCmp>(entity, pos, size);
        //reg.assign<RectRendCmp>(entity, borderColor, borderColor);
        reg.assign<StaticCollisionCmp>(entity);
    }
    {
        // right
        glm::vec2 size(1, winSize.y);
        glm::vec2 pos(winSize.x, winCenter.y);
        glm::ivec4 borderColor(255, 0, 0, 255);
        auto entity = reg.create();
        reg.assign<PositionCmp>(entity, pos, size);
        //reg.assign<RectRendCmp>(entity, borderColor, borderColor);
        reg.assign<StaticCollisionCmp>(entity);
    }
    {
        // top
        glm::vec2 size(winSize.x, 1);
        glm::vec2 pos(winCenter.x, 0);
        glm::ivec4 borderColor(255, 0, 0, 255);
        auto entity = reg.create();
        reg.assign<PositionCmp>(entity, pos, size);
        //reg.assign<RectRendCmp>(entity, borderColor, borderColor);
        reg.assign<StaticCollisionCmp>(entity);
    }
    {
        // bottom
        glm::vec2 size(winSize.x, 1);
        glm::vec2 pos(winCenter.x, winSize.y);
        glm::ivec4 borderColor(255, 0, 0, 255);
        auto entity = reg.create();
        reg.assign<PositionCmp>(entity, pos, size);
        //reg.assign<RectRendCmp>(entity, borderColor, borderColor);
        reg.assign<StaticCollisionCmp>(entity);
    }
}
