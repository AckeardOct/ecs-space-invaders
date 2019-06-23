#include "space_invaders.h"

#include <components/basic.h>
#include <components/render.h>


void ShipTpl::makeEntity(entt::registry &reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size, direction);
    //reg.assign<RectRendCmp>(entity, borderColor);
    reg.assign<SpriteRendCmp>(entity, spritePath);
    reg.assign<MoveCmp>(entity, speed);
    reg.assign<ShiftCollisionCmp>(entity);
    reg.assign<InputableCmp>(entity);
    reg.assign<GunCmp>(entity, rapidityOfFire_ms);
}


void InavaderTpl::makeEntity(entt::registry &reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size, direction);
    //reg.assign<RectRendCmp>(entity, borderColor);
    reg.assign<SpriteRendCmp>(entity, spritePath);
    reg.assign<MoveCmp>(entity, speed);
    reg.assign<ShiftCollisionCmp>(entity);
    //reg.assign<InputableCmp>(entity);
    reg.assign<GunCmp>(entity, rapidityOfFire_ms);
    reg.assign<AiGunCmp>(entity);
    reg.assign<AiRouteCmp>(entity, movePoints);
}


void WallTpl::makeEntity(entt::registry &reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size);
    //reg.assign<RectRendCmp>(entity, borderColor, borderColor);
    reg.assign<StaticCollisionCmp>(entity);
}


void BulletTpl::makeEntity(entt::registry& reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size, direction);
    //reg.assign<RectRendCmp>(entity, borderColor);
    reg.assign<SpriteRendCmp>(entity, spritePath, spriteScale);
    reg.assign<MoveCmp>(entity, speed);
    reg.assign<InertionCmp>(entity);
    reg.assign<OneShotCollisionCmp>(entity);
}
