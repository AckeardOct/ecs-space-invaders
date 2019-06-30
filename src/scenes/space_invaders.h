#pragma once

#include <scenes/i_scene.h>
#include <entt/entity/registry.hpp>
#include <vector>

class IBasicSys;
class IRenderSys;
class InputSys;

class EnemyCmp;
class PlayerCmp;

class SpaceInvaders;

class GameRule
{
public:
    GameRule(SpaceInvaders& scene)
        : scene(scene)
    { }

public:
    void initCallbacks     (entt::registry& reg);
    void update            ();

    void onConstructEnemy  (entt::registry& reg, entt::entity ent, EnemyCmp& cmp) { enemiesCount++; }
    void onDestroyEnemy    (entt::registry& reg, entt::entity ent) { enemiesCount--; }
    void onConstructPlayer (entt::registry& reg, entt::entity ent, PlayerCmp& cmp) { playersCount++; }
    void onDestroyPlayer   (entt::registry& reg, entt::entity ent) { playersCount--; }

public:
    int enemiesCount = 0;
    int playersCount = 0;

private:
    SpaceInvaders& scene;
};


class SpaceInvaders : public IScene
{
public:
    SpaceInvaders(GameWindow& window);

public:
    void win();
    void loose();

public: // IScene interface
    virtual void input(float dt, const SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render(float dt) override;    

private:
    void initBasicSystems();
    void initRenderSystems();
    void initEntities();

    void pauseBasicSystems();

private:
    GameRule gameRule;
    InputSys* inputSystem {nullptr};

    entt::registry           reg;
    std::vector<IBasicSys*>  basicSystems;
    std::vector<IRenderSys*> renderSystems;
};
