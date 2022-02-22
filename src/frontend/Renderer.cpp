#include <string>
#include <fmt/format.h>

#include "frontend/Renderer.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace slr {
    void Renderer::Init() {
        const std::string fontPath{"./resources/fonts/arvo.ttf"};
        sf::Font debugFont{};
        debugFont.loadFromFile(fontPath);
        mFonts[0] = debugFont;

        mDebugText.setFont(mFonts[0]);
        mDebugText.setCharacterSize(20U);
        mDebugText.setFillColor(sf::Color::Red);

        mDebugText.setPosition(sf::Vector2f{static_cast<float>(mWindow.getSize().x) - 200.f, 10.f});

        mWindow.setFramerateLimit(60);

        ImGui::SFML::Init(mWindow);
    }

    void Renderer::Render() {
        mView.Update(mDt.asSeconds());
        ImGui::SFML::Update(mWindow, mDt);

        mWindow.clear(sf::Color::Black);
        mEntityManager.Draw(mWindow);
        mDebugText.setString(fmt::format("fps: {:.3f}\nframetime: {:.3f}\n", 1.f / mDt.asSeconds(), mDt.asSeconds()));
        mWindow.draw(mDebugText);

        char windowTitle[255] = "ImGui + SFML = <3";

        ImGui::Begin("Sample window"); // begin window

        float color[3] = {0.f, 0.f, 0.f};

        sf::Color bgColor{};
        // Background color edit
        if (ImGui::ColorEdit3("Background color", color)) {
            // this code gets called if color value changes, so
            // the background color is upgraded automatically!
            bgColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            bgColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            bgColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        // Window title text edit
        ImGui::ShowDemoWindow();

        ImGui::InputText("Window title", windowTitle, 255);

        if (ImGui::Button("Update window title")) {
            // this code gets if user clicks on the button
            // yes, you could have written if(ImGui::InputText(...))
            // but I do this to show how buttons work :)
            mWindow.setTitle(windowTitle);
        }

        ImGui::End(); // end window

        mWindow.setView(mView);
        ImGui::SFML::Render(mWindow);
        mWindow.display();
    }
}
