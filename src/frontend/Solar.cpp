#include <ctime>
#include <iostream>
#include <fmt/format.h>

#include "frontend/Solar.h"

void Solar::Run() {
    while (mWindow.isOpen()) {
        Review();
        Update();
        Render();
    }
}

void Solar::Initialize() {
    mWindow.setFramerateLimit(60);
    mWorld.AddObject(std::make_unique<Object>(Vec3f(0, 0, 0), Vec3f(0, 0, 0), 10));
}

void Solar::Review() {
    sf::Event event;

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
                        
                    case sf::Keyboard::Left:
                        mView.move(sf::Vector2f{ -VIEW_MOVE_AMOUNT, 0.0f });
                        break;

                    case sf::Keyboard::Down:
                        mView.move(sf::Vector2f{ 0.0f, VIEW_MOVE_AMOUNT });
                        break;

                    case sf::Keyboard::Right:
                        mView.move(sf::Vector2f{ VIEW_MOVE_AMOUNT, 0.0f });
                        break;

                    case sf::Keyboard::Up:
                        mView.move(sf::Vector2f{ 0.0f, -VIEW_MOVE_AMOUNT });
                        break;
                        
                    case sf::Keyboard::K:
                        mView.zoom(1.0f / VIEW_ZOOM_FACTOR);
                        break;

                    case sf::Keyboard::J:
                        mView.zoom(VIEW_ZOOM_FACTOR);
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
    sf::Time dt = mDeltaClock.restart();
    mWorld.Step(dt.asSeconds());

    fmt::print("Frametime {}\nFPS {}\n", dt.asSeconds(), 1.f / dt.asSeconds());
}

void Solar::Render() {
    mWindow.clear(sf::Color::White);

    for (auto & obj : mWorld.GetObjects()) {
        sf::CircleShape c{ 100.f, 100 };
        c.setPosition(sf::Vector2f{ obj->GetPosition().x, obj->GetPosition().y });
        c.setFillColor(sf::Color::Red);
        mWindow.draw(c);
    }

    mWindow.setView(mView);
    mWindow.display();
}
