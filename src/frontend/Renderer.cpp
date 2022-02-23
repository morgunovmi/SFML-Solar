#include <string>
#include <fmt/format.h>

#include "frontend/Renderer.h"

namespace slr {
    void Renderer::Init() {

        mDebugText.setFont(mFonts[0]);
        mDebugText.setCharacterSize(20U);
        mDebugText.setFillColor(sf::Color::Red);

        mDebugText.setPosition(sf::Vector2f{static_cast<float>(mWindow.getSize().x) - 200.f, 10.f});

        mWindow.setFramerateLimit(60);
    }

    void Renderer::Render() {
        mView.Update(mDt.asSeconds());

        mWindow.clear(sf::Color::Black);
        mEntityManager.Draw(mWindow);
        mDebugText.setString(fmt::format("fps: {:.3f}\nframetime: {:.3f}\n", 1.f / mDt.asSeconds(), mDt.asSeconds()));
        mWindow.draw(mDebugText);

        mWindow.setView(mView);
    }

    void Renderer::Display() {
        mWindow.display();
    }
}
