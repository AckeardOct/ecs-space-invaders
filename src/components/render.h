#pragma once

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class RectRendCmp {
public:
    RectRendCmp(glm::ivec4 borderColor, glm::ivec4 fillColor = glm::ivec4{0});

public:
    glm::ivec4 borderColor;
    glm::ivec4 fillColor;    
};


class SpriteRendCmp {
public:
    SpriteRendCmp(const char* spritePath, glm::vec2 scale = glm::vec2(1.f, 1.f))
        : spritePath(spritePath)
        , scale(scale)
    { }

public:
    const char* spritePath;
    glm::vec2 scale;
};
