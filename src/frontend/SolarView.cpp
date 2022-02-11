#include "frontend/SolarView.h"

namespace slr {
    void SolarView::Update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            move(sf::Vector2f{-VIEW_MOVE_AMOUNT * mZoomLevel, 0.0f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            move(sf::Vector2f{VIEW_MOVE_AMOUNT * mZoomLevel, 0.0f});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            move(sf::Vector2f{0.0f, -VIEW_MOVE_AMOUNT * mZoomLevel});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            move(sf::Vector2f{0.0f, VIEW_MOVE_AMOUNT * mZoomLevel});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            zoom(VIEW_ZOOM_FACTOR);
            mZoomLevel *= VIEW_ZOOM_FACTOR;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            zoom(1.0f / VIEW_ZOOM_FACTOR);
            mZoomLevel /= VIEW_ZOOM_FACTOR;
        }
    }
}