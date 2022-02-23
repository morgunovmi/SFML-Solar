#ifndef SOLAR_GUI_H
#define SOLAR_GUI_H

#include <SFML/Graphics.hpp>

namespace slr {
    class GUI {
    public:
        GUI(sf::RenderWindow& window, sf::Time& dt) : mWindow(window), mDt(dt) {}

        bool Init();

        void Update();

        void Render();

        void Shutdown();

    private:
        void PollEvents();

    private:
        sf::RenderWindow&   mWindow;

        sf::Time&           mDt;
    };
}

#endif //SOLAR_GUI_H
