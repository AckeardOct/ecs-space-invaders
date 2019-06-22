#include "utils.h"
#include <common/logger.h>
#include <cmath>
#include <SDL2/SDL_test.h>

bool Ut::equal(float one, float two)
{
    const float diff = 0.0000000001f;
    return std::abs(one - two) < diff;
}


float Ut::toDeg(float rad)
{
    const float conv = 180 / M_PI;
    return rad * conv;
}


float Ut::toRad(float deg)
{
    const float conv = M_PI / 180;
    return deg * conv;
}


float Ut::calcAngle(glm::vec2 one, glm::vec2 two)
{
    float scalar = (one.x * two.x) + (one.y * two.y);
    float oneLength = std::sqrt(std::pow(one.x, 2) + std::pow(one.y, 2));
    float twoLength = std::sqrt(std::pow(two.x, 2) + std::pow(two.y, 2));
    float cosPhi = scalar / (oneLength * twoLength);
    return std::acos(cosPhi);
}


float Ut::toAngle(glm::vec2 direction)
{
    const glm::vec2 origin(0, -1);
    return calcAngle(direction, origin);
}


void Ut::tests()
{
    // toDeg
    {
        assert(Ut::equal(Ut::toDeg(M_PI), 180.f));
        assert(Ut::equal(Ut::toDeg(M_PI_2), 90.f));
        assert(Ut::equal(Ut::toDeg(M_PI_4), 45.f));
    }

    // toRad
    {
        assert(Ut::equal(Ut::toRad(180.f), M_PI));
        assert(Ut::equal(Ut::toRad(90.f), M_PI_2));
        assert(Ut::equal(Ut::toRad(45.f), M_PI_4));
    }

    // calcAngle
    {
        glm::vec2 one(0, -1);
        glm::vec2 two(0, 1);
        float angle = calcAngle(one, two);
        assert(Ut::equal(angle, M_PI));
    }
    {
        glm::vec2 one(0, -1);
        glm::vec2 two(0, -1);
        float angle = calcAngle(one, two);
        assert(Ut::equal(angle, 0));
    }
    {
        glm::vec2 one(0, -1);
        glm::vec2 two(1, -1);
        float angle = calcAngle(one, two);
        assert(Ut::equal(angle, M_PI_4));
    }
    {
        glm::vec2 one(0, -1);
        glm::vec2 two(1, 1);
        float angle = calcAngle(one, two);
        assert(Ut::equal(angle, 3 * M_PI_4));
    }
}

