#include "space_invaders.h"
#include <components/basic.h>
#include <components/render.h>
#include <systems/basic.h>
#include <systems/render.h>
#include <ents/space_invaders.h>


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
    basicSystems.push_back(new InertionSys());
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
        glm::vec2 size(30, 30);
        glm::vec2 pos(winCenter.x, winSize.y - size.y/1.5f);
        glm::vec2 direction(0.f, -1.f);
        glm::vec2 speed(150, 150);
        glm::ivec4 borderColor(255, 0, 0, 255);
        auto spritePath = "resources/images/pixel_ship.png";
        auto entity = reg.create();
        reg.assign<PositionCmp>(entity, pos, size, direction);
        //reg.assign<RectRendCmp>(entity, borderColor);
        reg.assign<SpriteRendCmp>(entity, spritePath);
        reg.assign<MoveCmp>(entity, speed);
        reg.assign<ShiftCollisionCmp>(entity);
        reg.assign<InputableCmp>(entity);
        reg.assign<GunCmp>(entity);
    }


    { // walls
        WallTpl wall;
        // left
        wall.size = glm::vec2(1, winSize.y);
        wall.pos  = glm::vec2(0, winCenter.y);
        wall.makeEntity(reg);
        // right
        wall.pos = glm::vec2(winSize.x, winCenter.y);
        wall.makeEntity(reg);
        // top
        wall.size = glm::vec2(winSize.x, 1);
        wall.pos  = glm::vec2(winCenter.x, 0);
        wall.makeEntity(reg);
        // bottom
        wall.pos  = glm::vec2(winCenter.x, winSize.y);
        wall.makeEntity(reg);
    }    
}
