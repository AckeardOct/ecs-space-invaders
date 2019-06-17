#pragma once

#include <scenes/i_scene.h>
#include <entt/entity/registry.hpp>
#include <vector>

class IBasicSys;
class IRenderSys;
class InputSys;

class SpaceInvaders : public IScene
{
public:
    SpaceInvaders(GameWindow& window);

public: // IScene interface
    virtual void input(float dt, const SDL_Event& event) override;
    virtual void update(float dt) override;
    virtual void render(float dt) override;

private:
    void initBasicSystems();
    void initRenderSystems();
    void initEntities();

private:
    InputSys* inputSystem {nullptr};

    entt::registry           reg;
    std::vector<IBasicSys*>  basicSystems;
    std::vector<IRenderSys*> renderSystems;
};
