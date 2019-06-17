#pragma once

#include <glm/vec2.hpp>

struct PositionCmp {
    glm::vec2 pos;
    glm::vec2 size;
    glm::vec2 oldPos;

public:
    PositionCmp(glm::vec2 pos, glm::vec2 size)
        : pos(pos)
        , size(size)
    {}
};


struct MoveCmp {
    glm::vec2 speed;

public:
    MoveCmp() = delete;
    MoveCmp(glm::vec2 speed)
        : speed(speed) {}

    void move(PositionCmp& posCmp, glm::vec2& direction, float dt);
};


struct StaticCollisionCmp {
};


struct ShiftCollisionCmp {
};
