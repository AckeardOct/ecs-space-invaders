#pragma once

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_assert.h>

#define LogMsg(format, args...) \
    SDL_Log(format, ## args)

#define LogError(format, args...) \
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, format, ## args)

#define LogCritical(format, args...) \
    SDL_LogCritical(SDL_LOG_CATEGORY_ASSERT, format, ## args); \
    SDL_assert(false)
