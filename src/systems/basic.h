#pragma once

#include <entt/entity/registry.hpp>
#include <SDL2/SDL_events.h>
#include <vector>
#include <unordered_map>

class PositionCmp;
class MoveCmp;


class IBasicSys
{
public:
    virtual void update(entt::registry& reg, float dt) = 0;
};


class InputSys : public IBasicSys
{
public:
    void onInput (const SDL_Event& event);

public: // IBasicSys interface
    virtual void update(entt::registry &reg, float dt) override;

private:
    std::vector<SDL_Event> events;
    std::unordered_map<int, bool> keys;
};


class InertionSys : public IBasicSys
{
public: // IBasicSys interface
    virtual void update(entt::registry &reg, float dt) override;
};


class CollisionSys : public IBasicSys
{
public: // IBasicSys interface
    virtual void update(entt::registry &reg, float dt) override;

private:
    bool isIntesects(PositionCmp& onePos, PositionCmp& twoPos);
    void resolveStaticShift(PositionCmp& staticPos, PositionCmp& shiftPos, MoveCmp& shiftMove);
    void resolveShiftShift(PositionCmp& onePos, MoveCmp& oneMove, PositionCmp& twoPos, MoveCmp& twoMove);
};


class SlayerSys : public IBasicSys
{
public: // IBasicSys interface
    virtual void update(entt::registry &reg, float dt) override;
};


class AiRouteSys : public IBasicSys
{
public: // IBasicSys interface
    virtual void update(entt::registry &reg, float dt) override;
};


class AiFireSys : public IBasicSys
{
public: // IBasicSys interface
    virtual void update(entt::registry &reg, float dt) override;
};
