#include <cstddef>
#include <cstdint>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "physics/PhysicsWorld.h"

class Solar {
    public:
        Solar(uint16_t width, uint16_t height) :
            mWindowWidth(width), mWindowHeight(height),
            mWindow(sf::VideoMode{ width, height }, "Solar System", sf::Style::Close,
                    sf::ContextSettings(0, 0, 8, 2, 0)),
            mView(sf::FloatRect{ 0, 0, static_cast<float>(width), static_cast<float>(height) }),
            mDeltaClock(), mWorld(Vec3f{ 0, 98.1f, 0 }),
            mTrailsPoints(), mDebugFont(), mDebugText(), mZoomLevel(1.f) {
                Initialize();
            }

        void Run();

    private:
        void Initialize();

        void Review();
        void Update();
        void Render();

        uint16_t            mWindowWidth, mWindowHeight;
        sf::RenderWindow    mWindow;
        sf::View            mView;

        sf::Clock           mDeltaClock;
        float               mDeltaSeconds{};
        
        PhysicsWorld        mWorld;
        std::vector<sf::Vertex> mTrailsPoints;

        sf::Font            mDebugFont;
        sf::Text            mDebugText;

        const float         VIEW_MOVE_AMOUNT = 10.f;
        const float         VIEW_ZOOM_FACTOR = 1.2f;
        float               mZoomLevel;
};
