#include "frontend/App.h"

#include "imgui-SFML.h"

namespace slr{
    void App::Init() {
        sf::Texture planets{};
        planets.loadFromFile("./resources/images/planet.png");
        mTextures[0] = planets;
    }

    void App::Run() {
        mGame.Init();
        mGUI.Init();
        while (mWindow.isOpen()) {
            mGame.Update();
            mGUI.Update();
            mRenderer.Render();
            mGUI.Render();
            mRenderer.Display();
        }
        mGUI.Shutdown();
    }
}