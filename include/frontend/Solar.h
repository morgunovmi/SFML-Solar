#ifndef SOLAR_H
#define SOLAR_H

#include <cstddef>
#include <cstdint>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "physics/PhysicsWorld.h"
#include "frontend/SolarView.h"

namespace slr {
    class Solar {
    public:
        Solar(uint16_t width, uint16_t height) :
                mWindowWidth(width), mWindowHeight(height),
                mWindow(sf::VideoMode{width, height}, "Solar System", sf::Style::Close,
                        sf::ContextSettings(0, 0, 8, 2, 0)),
                mView(width, height),
                mDeltaClock(), mWorld(Vec3f{0, 98.1f, 0}),
                mTrailsPoints(), mDebugFont(), mDebugText() {
            Initialize();
        }

        void Run();

    private:
        void Initialize();

        void Review();

        void Update();

        void Render();

        uint16_t mWindowWidth, mWindowHeight;
        sf::RenderWindow mWindow;
        SolarView mView;

        sf::Clock mDeltaClock;
        float mDeltaSeconds{};

        PhysicsWorld mWorld;
        std::vector<sf::Vertex> mTrailsPoints;

        sf::Font mDebugFont;
        sf::Text mDebugText;
    };
}

#endif