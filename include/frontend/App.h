#ifndef SOLAR_APP_H
#define SOLAR_APP_H

#include "SFML/Graphics.hpp"

#include "entities/EntityManager.h"
#include "Renderer.h"
#include "backend/Game.h"
#include "frontend/GUI.h"
#include "misc/Log.h"

namespace slr {
    class App {
    public:
        App(uint16_t width, uint16_t height, const sf::ContextSettings& settings) :
                mWindowWidth(width), mWindowHeight(height), mSettings(settings),
                mWindow(sf::VideoMode{width, height},
                        "Solar System", sf::Style::Close, settings),
                mDeltaClock(), mDt(),
                mRenderer(mWindow, mDt, mEntityManager, mFonts, mTextures, mAppLog),
                mGame(mWindow, mDeltaClock, mDt, mEntityManager, mAppLog),
                mGUI(mWindow, mDt, mAppLog),
                mEntityManager(mTextures, mAppLog),
                mFonts(), mTextures(),
                mAppLog() {}

        void Init();
        void Run();

    private:
        uint16_t                        mWindowWidth, mWindowHeight;
        sf::ContextSettings             mSettings;

        sf::RenderWindow                mWindow;

        sf::Clock                       mDeltaClock;
        sf::Time                        mDt;

        Renderer                        mRenderer;
        Game                            mGame;
        GUI                             mGUI;

        EntityManager                   mEntityManager;
        std::array<sf::Font, 1>         mFonts;
        std::array<sf::Texture, 1>      mTextures;

        //TODO Make it global somehow
        Log                             mAppLog;
    };
}

#endif //SOLAR_APP_H
