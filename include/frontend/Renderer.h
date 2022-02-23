#ifndef SOLAR_H
#define SOLAR_H

#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "frontend/SolarView.h"
#include "entities/EntityManager.h"

#include "RendererEnums.h"

namespace slr {
    class Renderer {
    public:
        Renderer(sf::RenderWindow& window, sf::Time& dt, EntityManager& entityManager,
                 std::array<sf::Font, 1>& fonts, std::array<sf::Texture, 1>& textures) :
                mWindow(window), mView(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)),
                mDt(dt), mEntityManager(entityManager),
                mFonts(fonts), mTextures(textures), mDebugText() {
            Init();
        }

        void Render();

        void Display();

    private:
        void Init();

    private:
        sf::RenderWindow&           mWindow;
        SolarView                   mView;

        sf::Time&                   mDt;

        EntityManager&              mEntityManager;
        std::array<sf::Font, 1>&    mFonts;
        std::array<sf::Texture, 1>& mTextures;
        sf::Text                    mDebugText;
    };
}

#endif