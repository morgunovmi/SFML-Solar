#include <iostream>

#include "frontend/Solar.h"

void Solar::Run() {
    while (mWindow.isOpen()) {
        Review();
        Update();
        Render();
    }
}

void Solar::Initialize() {
    mCircle.setFillColor(sf::Color::Red);
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
                        mView.move(sf::Vector2f(-VIEW_MOVE_AMOUNT, 0.0f));
                        break;

                    case sf::Keyboard::Down:
                        mView.move(sf::Vector2f(0.0f, VIEW_MOVE_AMOUNT));
                        break;

                    case sf::Keyboard::Right:
                        mView.move(sf::Vector2f(VIEW_MOVE_AMOUNT, 0.0f));
                        break;

                    case sf::Keyboard::Up:
                        mView.move(sf::Vector2f(0.0f, -VIEW_MOVE_AMOUNT));
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

    mCircle.move(sf::Vector2f{ 100.f * dt.asSeconds(), 0.f });
}

void Solar::Render() {
    mWindow.clear();
    mWindow.setView(mView);
    mWindow.draw(mCircle);
    mWindow.display();
}
