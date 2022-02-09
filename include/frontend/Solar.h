#include <cstdint>

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
            mDeltaClock(), mWorld(Vec3f{ 0, 98.1, 0 }) {
                Initialize();
            }

        ~Solar() noexcept = default;

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
        PhysicsWorld        mWorld;

        const float         VIEW_MOVE_AMOUNT = 10.f;
        const float         VIEW_ZOOM_FACTOR = 1.2f;
};
