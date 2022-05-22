#include "frontend/App.h"
#include "misc/Log.h"

#include "imgui-SFML.h"

namespace slr {
    void App::Init() {
        const std::string fontPath{"./resources/fonts/arvo.ttf"};
        sf::Font debugFont{};
        debugFont.loadFromFile(fontPath);
        mFonts[0] = debugFont;

        sf::Texture planets{};
        planets.loadFromFile("./resources/images/planet.png");
        mTextures[0] = planets;
    }

    void App::Run() {
        mGame.Init();
        mGUI.Init();
        while (mWindow.isOpen()) {
            mDt = mDeltaClock.restart();
            mGame.Update();
            mGUI.Update();
            mRenderer.Render();
            mGUI.Render();
            mRenderer.Display();
        }
        mGUI.Shutdown();
    }
}
