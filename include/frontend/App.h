#ifndef SOLAR_APP_H
#define SOLAR_APP_H

#include "SFML/Graphics.hpp"

#include "entities/EntityManager.h"
#include "Renderer.h"
#include "backend/Game.h"

namespace slr {
    class App {
    public:
        App(uint16_t width, uint16_t height, const sf::ContextSettings& settings) :
                mWindowWidth(width), mWindowHeight(height), mSettings(settings),
                mWindow(sf::VideoMode{width, height},
                        "Solar System", sf::Style::Close, settings),
                mDeltaClock(), mDt(),
                mRenderer(mWindow, mDt, mEntityManager, mTextures),
                mGame(mWindow, mDeltaClock, mDt, mEntityManager),
                mEntityManager(mTextures) {}

        void Init();
        void Run();

    private:
        uint16_t            mWindowWidth, mWindowHeight;
        sf::ContextSettings mSettings;

        sf::RenderWindow    mWindow;

        sf::Clock           mDeltaClock;
        sf::Time            mDt;

        Renderer            mRenderer;
        Game                mGame;

        EntityManager       mEntityManager;
        std::array<sf::Texture, 1>  mTextures;
    };
}

#endif //SOLAR_APP_H
