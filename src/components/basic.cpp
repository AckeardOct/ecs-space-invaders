#include "basic.h"
#include <chrono>


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

bool GunCmp::isTimeToFire(bool updateTime)
{
    auto duration  = std::chrono::system_clock::now().time_since_epoch();
    auto current_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    if (current_ms - lastFire_ms > rapidityOfFire_ms) {
        if (updateTime) {
            lastFire_ms = current_ms;
        }
        return true;
    }
    return false;
}
