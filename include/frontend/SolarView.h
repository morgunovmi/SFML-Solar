#ifndef SOLAR_SOLARVIEW_H
#define SOLAR_SOLARVIEW_H

#include <SFML/Graphics.hpp>

namespace slr {
    const float VIEW_MOVE_AMOUNT = 10.f;
    const float VIEW_ZOOM_FACTOR = 1.2f;

    class SolarView : public sf::View {
    public:
        SolarView(float width, float height) :
                sf::View(sf::FloatRect{0, 0, width, height}),
                mMoveVelocity(), mZoomSpeed(), mZoomLevel(1.f) {}

        void Update();

        float GetZoomLevel() const {
            return mZoomLevel;
        }

        const sf::Vector2f& GetMoveVelocity() const {
            return mMoveVelocity;
        }

        float GetZoomSpeed() const {
            return mZoomSpeed;
        }

        void SetMMoveVelocity(const sf::Vector2f& moveVelocity) {
            SolarView::mMoveVelocity = moveVelocity;
        }

        void SetMZoomSpeed(float zoomSpeed) {
            SolarView::mZoomSpeed = zoomSpeed;
        }

        void SetMZoomLevel(float zoomLevel) {
            SolarView::mZoomLevel = zoomLevel;
        }

    private:
        sf::Vector2f mMoveVelocity;
        float mZoomSpeed;
        float mZoomLevel;
    };
}

#endif //SOLAR_SOLARVIEW_H
