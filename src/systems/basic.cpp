#include "basic.h"
#include <components/basic.h>
#include <components/render.h>
#include <common/logger.h>
#include <ents/space_invaders.h>

#include <glm/glm.hpp>


void InputSys::onInput(const SDL_Event &event)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
        if (false == keys[event.key.keysym.sym]) {
            keys[event.key.keysym.sym] = true;
            events.push_back(event);
        }
        break;
    case SDL_KEYUP:
        if (true == keys[event.key.keysym.sym]) {
            keys[event.key.keysym.sym] = false;
            events.push_back(event);
        }
        break;    
    }
}


void InputSys::update(entt::registry &reg, float dt)
{
    glm::vec2 direction(0, 0);
    for (auto& iter : keys) {
        if (iter.second) {
            switch(iter.first) {
            case SDLK_UP:
                direction.y -= 1.f;
                break;
            case SDLK_DOWN:
                direction.y += 1.f;
                break;
            case SDLK_LEFT:
                direction.x -= 1.f;
                break;
            case SDLK_RIGHT:
                direction.x += 1.f;
                break;
            }
        }
    }

    auto moveView = reg.view<PositionCmp, MoveCmp, InputableCmp>();
    for (auto et : moveView) {
        if (direction.length() > 0.1) {
            glm::normalize(direction);
            PositionCmp& posCmp = moveView.get<PositionCmp>(et);
            MoveCmp& moveCmp    = moveView.get<MoveCmp>(et);
            moveCmp.move(posCmp, direction, dt);
        }
    }

    auto fireView = reg.view<PositionCmp, GunCmp, InputableCmp>();
    for (auto et : fireView) {
        for (auto ev : events) {
            if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE) {
                PositionCmp& posCmp = moveView.get<PositionCmp>(et);
                BulletTpl bullet;
                bullet.pos = posCmp.pos;
                bullet.pos += posCmp.direction * (bullet.size/2.f + posCmp.size/2.f);
                bullet.direction = posCmp.direction;
                bullet.makeEntity(reg);
            }
        }
    }

    events.clear();
}


void InertionSys::update(entt::registry &reg, float dt)
{
    auto view = reg.view<PositionCmp, MoveCmp, InertionCmp>();
    for (auto ent : view) {
        PositionCmp& posCmp = view.get<PositionCmp>(ent);
        MoveCmp& moveCmp = view.get<MoveCmp>(ent);

        moveCmp.move(posCmp, dt);
    }
}


void CollisionSys::update(entt::registry &reg, float dt)
{
    auto staticView = reg.view<PositionCmp, StaticCollisionCmp>();
    auto shiftView = reg.view<PositionCmp, ShiftCollisionCmp, MoveCmp>();
    auto oneShotView = reg.view<PositionCmp, OneShotCollisionCmp>();

    for (auto staticEnt : staticView) {
        PositionCmp& staticPosCmp = staticView.get<PositionCmp>(staticEnt);

        for (auto shiftEnt : shiftView) {
            PositionCmp& shiftPosCmp = shiftView.get<PositionCmp>(shiftEnt);
            MoveCmp& shiftMoveCmp = shiftView.get<MoveCmp>(shiftEnt);
            resolveStaticShift(staticPosCmp, shiftPosCmp, shiftMoveCmp);
        }

        for (auto oneShotEnt : oneShotView) {
            PositionCmp& oneShotPosCmp = oneShotView.get<PositionCmp>(oneShotEnt);
            if (isIntesects(staticPosCmp, oneShotPosCmp)) {
                reg.destroy(oneShotEnt);
            }
        }
    }
}


class AABB {
public:
    AABB(glm::vec2 pos, glm::vec2 size) {
        min = pos - size / 2.f;
        max = pos + size / 2.f;
    }

    glm::ivec2 min;
    glm::ivec2 max;

    static bool isIntersect(AABB& one, AABB& two) {
        if(one.max.x < two.min.x || one.min.x > two.max.x)
            return false;
        if(one.max.y < two.min.y || one.min.y > two.max.y)
            return false;
        return true;
    }
};


bool CollisionSys::isIntesects(PositionCmp &onePos, PositionCmp &twoPos)
{
    AABB oneAABB(onePos.pos, onePos.size);
    AABB twoAABB(twoPos.pos, twoPos.size);

    return AABB::isIntersect(oneAABB, twoAABB);
}


void CollisionSys::resolveStaticShift(PositionCmp &staticPos, PositionCmp &shiftPos, MoveCmp &shiftMove)
{
    AABB staticAABB(staticPos.pos, staticPos.size);
    AABB shiftAABB(shiftPos.pos, shiftPos.size);

    if (! AABB::isIntersect(staticAABB, shiftAABB)) {
        return;
    }

    glm::vec2 direction = shiftPos.oldPos - shiftPos.pos;
    glm::normalize(direction);
    assert(direction.length() > 1.5f);

    int count = 0;
    while (AABB::isIntersect(staticAABB, shiftAABB)) {
        const float dt = 1.f;
        shiftMove.move(shiftPos, direction, dt);
        staticAABB = AABB(staticPos.pos, staticPos.size);
        shiftAABB  = AABB(shiftPos.pos, shiftPos.size);
        count++;
        assert(count < 1000);
    }
}
