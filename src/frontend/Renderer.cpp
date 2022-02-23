#include <string>
#include <fmt/format.h>

#include "frontend/Renderer.h"

namespace slr {
    void Renderer::Init() {
        mWindow.setFramerateLimit(60);
    }

    void Renderer::Render() {
        mView.Update(mDt.asSeconds());

        mWindow.clear(sf::Color::Black);
        mEntityManager.Draw(mWindow);

        mWindow.setView(mView);
    }

    void Renderer::Display() {
        mWindow.display();
    }
}
