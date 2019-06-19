#include "space_invaders.h"

#include <components/basic.h>
#include <components/render.h>


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
