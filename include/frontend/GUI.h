#ifndef SOLAR_GUI_H
#define SOLAR_GUI_H

#include <SFML/Graphics.hpp>

namespace slr {
    class GUI {
    public:
        GUI(sf::RenderWindow& window, sf::Time& dt) : mWindow(window), mDt(dt),
            mShowMainMenuBar(false), mShowFrameInfoOverlay(false) {}

        bool Init();

        void Update();

        void Render();

        void Shutdown();

    private:
        void PollEvents();

        void ShowMainMenuBar();
        void ShowFrameInfoOverlay();

    private:
        sf::RenderWindow&   mWindow;
        sf::Time&           mDt;

        bool                mShowMainMenuBar;
        bool                mShowFrameInfoOverlay;
    };
}

#endif //SOLAR_GUI_H
