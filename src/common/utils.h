#pragma once

#include <glm/vec2.hpp>

namespace Ut {
    float getRandomPercentage();

    bool  equal(float one, float two);

    float toDeg(float rad);

    float toRad(float deg);

    float calcLength(glm::vec2 vec);

    float calcAngle(glm::vec2 one, glm::vec2 two); // rads

    float toAngle(glm::vec2 vec); // rads

    void  tests();
}
