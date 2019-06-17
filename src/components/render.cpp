#include "render.h"

#include <common/logger.h>

static bool checkColor(glm::ivec4& color)
{
    if (color.r < 0 || color.r > 255) {
        return false;
    }
    else if (color.g < 0 || color.g > 255) {
        return false;
    }
    else if (color.b < 0 || color.b > 255) {
        return false;
    }
    else if (color.a < 0 || color.a > 255) {
        return false;
    }
    return true;
}


RectRendCmp::RectRendCmp(glm::ivec4 borderColor, glm::ivec4 fillColor)
    : borderColor(borderColor)
    , fillColor(fillColor)
{
    if (!checkColor(borderColor)) {
        LogCritical("borderColor is invalid!");
    } else if (!checkColor(fillColor)) {
        LogCritical("fillColor is invalid!");
    }
}
