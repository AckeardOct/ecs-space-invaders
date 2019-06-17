#include "basic.h"
#include <components/basic.h>
#include <common/logger.h>

#include <glm/glm.hpp>

void InputSys::onInput(const SDL_Event &event)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
        keys[event.key.keysym.sym] = true;
        break;
    case SDL_KEYUP:
        keys[event.key.keysym.sym] = false;
        break;
    default:
        events.push_back(event);
        break;
    }
}


void InputSys::update(entt::registry &reg, float dt)
{
    auto view = reg.view<PositionCmp, MoveCmp>();
    for (auto et : view) {
        PositionCmp& posCmp = view.get<PositionCmp>(et);

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
        if (direction.length() > 0.1) {
            glm::normalize(direction);
            MoveCmp& moveCmp    = view.get<MoveCmp>(et);
            moveCmp.move(posCmp, direction, dt);
        }
    }

    events.clear();
}


void CollisionSys::update(entt::registry &reg, float dt)
{
    auto staticView = reg.view<PositionCmp, StaticCollisionCmp>();
    auto shiftView = reg.view<PositionCmp, ShiftCollisionCmp, MoveCmp>();

    for (auto staticEnt : staticView) {
        PositionCmp& staticPosCmp = staticView.get<PositionCmp>(staticEnt);

        for (auto shiftEnt : shiftView) {
            PositionCmp& shiftPosCmp = shiftView.get<PositionCmp>(shiftEnt);
            MoveCmp& shiftMoveCmp = shiftView.get<MoveCmp>(shiftEnt);
            resolveStaticShift(staticPosCmp, shiftPosCmp, shiftMoveCmp);
        }
    }
}

//bool colized(AABB one, AABB two)
//{
//    if(one.max.x < two.min.x || one.min.x > two.max.x)
//        return false;
//    if(one.max.y < two.min.y || one.min.y > two.max.y)
//        return false;
//    return true;
//}


class AABB {
public:
    AABB(glm::vec2 pos, glm::vec2 size) {
        min = pos - size / 2.f;
        //min -= 1;
        max = pos + size / 2.f;
        //max += 1;
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
