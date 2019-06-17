#pragma once

#include <glm/vec4.hpp>

class RectRendCmp {
public:
    RectRendCmp(glm::ivec4 borderColor, glm::ivec4 fillColor = glm::ivec4{0});

public:
    glm::ivec4 borderColor;
    glm::ivec4 fillColor;
};


class SpriteRendCmp {
public:
    SpriteRendCmp(const char* spritePath)
        : spritePath(spritePath)
    { }

public:
    const char* spritePath;
};
