#include <string>
#include <fmt/format.h>

#include <SFML/Graphics/RectangleShape.hpp>

#include "frontend/Solar.h"

namespace slr {
    void Solar::Run() {
        while (mWindow.isOpen()) {
            Review();
            Update();
            Render();
        }
    }

    void Solar::Initialize() {
        const std::string fontPath{"../resources/fonts/arvo.ttf"};

        mDebugFont.loadFromFile(fontPath);

        mDebugText.setFont(mDebugFont);
        mDebugText.setCharacterSize(20U);
        mDebugText.setFillColor(sf::Color::Red);

        mDebugText.setPosition(static_cast<float>(mWindowWidth) - 200.f, 10.f);

        mWindow.setFramerateLimit(60);
        for (size_t i = 0; i < 10; i++) {
            mWorld.CreateObject(
                    std::make_unique<Object>(Vec3f(rand() % 10000, 0, 0), Vec3f(0, rand() % 500, 0), 10000));
        }
    }

    void Solar::Review() {
        sf::Event event{};

        while (mWindow.pollEvent(event)) {
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

    void Solar::Update() {
        mDeltaSeconds = mDeltaClock.restart().asSeconds();
        mWorld.Step(mDeltaSeconds);
        mView.Update(mDeltaSeconds);
    }

    void Solar::Render() {
        mWindow.clear(sf::Color::White);

        sf::CircleShape sun{100.f, 100};
        sun.setOrigin(sun.getRadius(), sun.getRadius());
        sun.setPosition(0.f, 0.f);
        sun.setFillColor(sf::Color::Yellow);
        mWindow.draw(sun);

        for (auto& obj: mWorld.GetObjects()) {
            sf::CircleShape c{100.f, 100};
            c.setOrigin(c.getRadius(), c.getRadius());
            c.setPosition(sf::Vector2f{obj->GetPosition().x, obj->GetPosition().y});
            c.setFillColor(sf::Color::Red);

            mWindow.draw(c);

            const auto bbox = c.getGlobalBounds();
            sf::RectangleShape brect;
            brect.setPosition(sf::Vector2f{bbox.left, bbox.top});
            brect.setSize(sf::Vector2f{bbox.width, bbox.height});
            brect.setFillColor(sf::Color::Transparent);
            brect.setOutlineThickness(3.f);
            brect.setOutlineColor(sf::Color::Red);
            mWindow.draw(brect);

            mTrailsPoints.push_back(sf::Vertex{sf::Vector2f{
                    obj->GetPosition().x, obj->GetPosition().y}, sf::Color::Red});
        }

        mWindow.draw(&mTrailsPoints[0], mTrailsPoints.size(), sf::Points);

        mDebugText.setString(fmt::format("fps: {:.3f}\nframetime: {:.3f}\n", 1.f / mDeltaSeconds, mDeltaSeconds));
        mWindow.draw(mDebugText);

        mWindow.setView(mView);
        mWindow.display();
    }
}