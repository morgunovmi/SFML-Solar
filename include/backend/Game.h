#ifndef SOLAR_GAME_H
#define SOLAR_GAME_H

#include <random>

#include <SFML/Graphics.hpp>

#include "entities/EntityManager.h"
#include "physics/PhysicsWorld.h"

namespace slr {
    class Game {
    public:
        Game(sf::RenderWindow& window, sf::Clock& deltaClock, sf::Time& dt, EntityManager& entityManager) :
            mWindow(window), mDeltaClock(deltaClock), mDt(dt),
            mEntityManager(entityManager), mRd() {}

        void Init();
        void Update();

    private:
        void PollInput();

    private:
        sf::RenderWindow&                       mWindow;

        sf::Clock&                              mDeltaClock;
        sf::Time&                               mDt;

        EntityManager&                          mEntityManager;

        std::random_device                      mRd;
        std::default_random_engine              mDre{ mRd() };
        std::uniform_real_distribution<float>   mPosDistr{-1000.f, 1000.f};
        std::uniform_real_distribution<float>   mSpeedDistr{-2500.f, 2500.f};
        std::uniform_real_distribution<float>   mMassDistr{5000.f, 15000.f};
    };
}

#endif //SOLAR_GAME_H
