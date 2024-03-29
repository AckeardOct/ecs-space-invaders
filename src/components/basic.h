#pragma once

#include <glm/vec2.hpp>
#include <vector>

struct PositionCmp {    
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 direction;
    glm::vec2 oldPos;

public:
    PositionCmp(glm::vec2 pos, glm::vec2 size, glm::vec2 direction = glm::vec2(0.f, 0.f))
        : pos(pos)
        , size(size)
        , direction(direction)
    { }
};


struct MoveCmp {
    glm::vec2 speed;

public:
    MoveCmp() = delete;
    MoveCmp(glm::vec2 speed)
        : speed(speed) {}

    void move(PositionCmp& posCmp, float dt) { move(posCmp, posCmp.direction, dt); }
    void move(PositionCmp& posCmp, glm::vec2& direction, float dt);
};


struct GunCmp {
    int      rapidityOfFire_ms {0};
    long     lastFire_ms       {0};

    GunCmp(int rapidityOfFire_ms)
        : rapidityOfFire_ms(rapidityOfFire_ms)
    { }

    bool isTimeToFire(bool updateTime = false);
};


struct InputableCmp {
};


struct InertionCmp {
};


struct StaticCollisionCmp {
};


struct ShiftCollisionCmp {
};


struct OneShotCollisionCmp {
};


struct AiRouteCmp {
    std::vector<glm::vec2> points;

    AiRouteCmp(std::vector<glm::vec2>& points)
        : points(points)
    { }
};


struct AiGunCmp {
};


struct DeadCmp {
};


struct EnemyCmp {
};


struct PlayerCmp {
};
