#include "frontend/GUI.h"

#include "imgui-SFML.h"
#include "imgui.h"

namespace slr {
    bool GUI::Init() {
        return ImGui::SFML::Init(mWindow);
    }

    void GUI::PollEvents() {
        sf::Event event{};

        while (mWindow.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
        }
    }

    void GUI::Update() {
        PollEvents();
        ImGui::SFML::Update(mWindow, mDt);
    }

    void GUI::Render() {
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

        ImGui::SFML::Render(mWindow);
    }

    void GUI::Shutdown() {
        ImGui::SFML::Shutdown();
    }
}
