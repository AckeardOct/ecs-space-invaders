#include "space_invaders.h"

#include <components/basic.h>
#include <components/render.h>


unsigned int ShipTpl::makeEntity(entt::registry &reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size, direction);
    //reg.assign<RectRendCmp>(entity, borderColor);
    reg.assign<SpriteRendCmp>(entity, spritePath);
    reg.assign<MoveCmp>(entity, speed);
    reg.assign<ShiftCollisionCmp>(entity);
    reg.assign<InputableCmp>(entity);
    reg.assign<GunCmp>(entity, rapidityOfFire_ms);
    reg.assign<PlayerCmp>(entity);

    return entity;
}


unsigned int InavaderTpl::makeEntity(entt::registry &reg)
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
    reg.assign<EnemyCmp>(entity);

    return entity;
}


unsigned int WallTpl::makeEntity(entt::registry &reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size);
    //reg.assign<RectRendCmp>(entity, borderColor, borderColor);
    reg.assign<StaticCollisionCmp>(entity);

    return entity;
}


unsigned int BulletTpl::makeEntity(entt::registry& reg)
{
    auto entity = reg.create();
    reg.assign<PositionCmp>(entity, pos, size, direction);
    //reg.assign<RectRendCmp>(entity, borderColor);
    reg.assign<SpriteRendCmp>(entity, spritePath, spriteScale);
    reg.assign<MoveCmp>(entity, speed);
    reg.assign<InertionCmp>(entity);
    reg.assign<OneShotCollisionCmp>(entity);

    return entity;
}
