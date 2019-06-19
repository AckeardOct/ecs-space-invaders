#pragma once

#include <entt/entity/registry.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <components/basic.h>
#include <components/render.h>

struct IAbstractEnt {
    virtual void makeEntity(entt::registry& reg) = 0;
};


struct ShipTpl : public IAbstractEnt
{
    glm::vec2   size        {0, 0};
    glm::vec2   pos         {0, 0};
    glm::vec2   direction   {0, 0};
    glm::vec2   speed       {150, 150};
    glm::ivec4  borderColor {255, 0, 0, 255};
    const char* spritePath  {"resources/images/pixel_ship.png"};

    virtual void makeEntity(entt::registry &reg) override;
};


struct WallTpl : public IAbstractEnt
{
    glm::vec2  size        {0, 0};
    glm::vec2  pos         {0, 0};
    glm::ivec4 borderColor {255, 0, 0, 255};

    virtual void makeEntity(entt::registry &reg) override;
};


struct BulletTpl : public IAbstractEnt
{
    glm::vec2   pos         {0, 0};
    glm::vec2   direction   {0, 0};

    glm::vec2   size        {4, 10};
    glm::vec2   spriteScale {6.f, 3.5f};
    glm::vec2   speed       {300, 300};
    glm::ivec4  borderColor {255, 0, 0, 255};
    const char* spritePath  {"resources/images/pixel_laser_green.png"};

    virtual void makeEntity(entt::registry& reg) override;
};
