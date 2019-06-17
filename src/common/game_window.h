#pragma once

#include <glm/vec2.hpp>

class SDL_Window;
class SDL_Renderer;

class IScene;
class TextureBank;

class GameWindow
{
public:
    GameWindow(int argc, char** argv);
    ~GameWindow();

    void          runLoop        (void);
    glm::vec2     getSize        (void) const;
    SDL_Renderer& getRenderer    (void);
    TextureBank&  getTextureBank (void);

private:
    void initSDL      (void);
    void processInput (float dt);
    void update       (float dt);
    void render       (float dt);

private:
    SDL_Window*   sdl_window    {nullptr};
    SDL_Renderer* sdl_renderer  {nullptr};

    TextureBank*  textureBank   {nullptr};
    IScene*       scene         {nullptr};
    bool          quitRequested {false};
};
