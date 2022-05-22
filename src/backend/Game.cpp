#include "backend/Game.h"

#include "imgui-SFML.h"

#include "frontend/RendererEnums.h"

namespace slr {
    void Game::Init() {
        mEntityManager.CreateEntity(sf::Vector2f{0.f, 0.f},
                                    sf::Vector2f{-932.f, -864.f},
                                    65000.f, PLANET);

        mEntityManager.CreateEntity(sf::Vector2f{970.f, -243.f},
                                    sf::Vector2f{466.f, 432.f},
                                    65000.f, PLANET);

        mEntityManager.CreateEntity(sf::Vector2f{-970.f, 243.f},
                                    sf::Vector2f{466.f, 432.f},
                                    65000.f, PLANET);
    }

    void Game::Update() {
        PollInput();
        mEntityManager.Update(mDt.asSeconds());
    }

    void Game::PollInput() {
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
}
