#include "basic.h"


void MoveCmp::move(PositionCmp &posCmp, glm::vec2 &direction, float dt) {
    static const float diff = 0.5f;
    glm::vec2 tmpPos = posCmp.pos;
    float dtSecs = dt / 1000.f;
    double stepX = direction.x * dtSecs * speed.x;
    double stepY = direction.y * dtSecs * speed.y;
    posCmp.pos.x += stepX;
    posCmp.pos.y += stepY;

    if ((posCmp.oldPos - posCmp.pos).length() > diff) {
        posCmp.oldPos = tmpPos;
    }
}
