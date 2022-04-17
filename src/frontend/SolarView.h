#ifndef SOLAR_SOLARVIEW_H
#define SOLAR_SOLARVIEW_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

namespace slr {
    const float VIEW_ACCEL_AMOUNT = 25.f;
    const float VIEW_DAMP_FACTOR = 0.96f;
    const float VIEW_SPEED_CAP = 800.f;
    const float VIEW_ZOOM_FACTOR = 1.1f;

    class SolarView : public sf::View {
    public:
        SolarView(float width, float height) :
                sf::View(sf::FloatRect(
                            sf::Vector2f{0, 0},
                            sf::Vector2f{width, height}
                            )
                        ),
                mMoveVelocity(), mZoomSpeed(), mZoomLevel(1.f) {}

        void Update(float dt);

        float GetZoomLevel() const {
            return mZoomLevel;
        }

        const sf::Vector2f& GetMoveVelocity() const {
            return mMoveVelocity;
        }

        float GetZoomSpeed() const {
            return mZoomSpeed;
        }

        void SetMoveVelocity(const sf::Vector2f& moveVelocity) {
            SolarView::mMoveVelocity = moveVelocity;
        }

        void SetZoomSpeed(float zoomSpeed) {
            SolarView::mZoomSpeed = zoomSpeed;
        }

        void SetZoomLevel(float zoomLevel) {
            SolarView::mZoomLevel = zoomLevel;
        }

    private:
        sf::Vector2f    mMoveVelocity;
        float           mZoomSpeed;
        float           mZoomLevel;
    };
}

#endif //SOLAR_SOLARVIEW_H
