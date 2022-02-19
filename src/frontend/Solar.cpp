#include <string>
#include <fmt/format.h>

#include "frontend/Solar.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace slr {
    void Solar::Run() {
        while (mWindow.isOpen()) {
            Review();
            Update(mDeltaClock.restart());
            Render();
        }
        ImGui::SFML::Shutdown();
    }

    void Solar::Initialize() {
        const std::string fontPath{"../resources/fonts/arvo.ttf"};

        mDebugFont.loadFromFile(fontPath);

        mDebugText.setFont(mDebugFont);
        mDebugText.setCharacterSize(20U);
        mDebugText.setFillColor(sf::Color::Red);

        mDebugText.setPosition(static_cast<float>(mWindowWidth) - 200.f, 10.f);

        mWindow.setFramerateLimit(60);

        ImGui::SFML::Init(mWindow);

        mPlanetsSheet.loadFromFile("../resources/images/planet.png");

        mEntityManager.CreateEntity(sf::Vector2f{0.f, 0.f},
                                    sf::Vector2f{-932.f, -864.f},
                                    65000.f, mPlanetsSheet);

        mEntityManager.CreateEntity(sf::Vector2f{970.f, -243.f},
                                    sf::Vector2f{466.f, 432.f},
                                    65000.f, mPlanetsSheet);

        mEntityManager.CreateEntity(sf::Vector2f{-970.f, 243.f},
                                    sf::Vector2f{466.f, 432.f},
                                    65000.f, mPlanetsSheet);
    }

    void Solar::Review() {
        sf::Event event{};

        while (mWindow.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type) {
                case sf::Event::Closed:
                    mWindow.close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Escape:
                            mWindow.close();
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    void Solar::Update(sf::Time dt) {
        const auto dtSeconds = dt.asSeconds();
        mEntityManager.Update(dtSeconds);
        mView.Update(dtSeconds);
        ImGui::SFML::Update(mWindow, dt);
    }

    void Solar::Render() {
        mWindow.clear(sf::Color::Black);

        /*
        sf::CircleShape sun{100.f, 100};
        sun.setOrigin(sun.getRadius(), sun.getRadius());
        sun.setPosition(0.f, 0.f);
        sun.setFillColor(sf::Color::Yellow);
        mWindow.draw(sun);
         */

        /*
        sf::Image img{};
        img.loadFromFile("../resources/images/planet.png");
        sf::Texture tex{};
        tex.loadFromImage(img);
        sf::Sprite sprite(tex);
        mWindow.draw(sprite);
         */

        mEntityManager.Draw(mWindow);


        mDebugText.setString(fmt::format("fps: {:.3f}\nframetime: {:.3f}\n", 1.f / mDeltaSeconds, mDeltaSeconds));
        mWindow.draw(mDebugText);

        char windowTitle[255] = "ImGui + SFML = <3";


        /*
        ImGui::Begin("Sample window"); // begin window

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
        */
//        ImGui::End(); // end window

        mWindow.setView(mView);
        ImGui::SFML::Render(mWindow);
        mWindow.display();
    }
}
