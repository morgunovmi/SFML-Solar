#ifndef SOLAR_GUI_H
#define SOLAR_GUI_H

#include <queue>

#include <SFML/Graphics.hpp>

namespace slr {
    const uint16_t FRAME_QUEUE_SIZE = 60;

    class GUI {
    public:
        GUI(sf::RenderWindow& window, sf::Time& dt) : mWindow(window), mDt(dt),
            mFrameTimeQueue(),
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

        std::queue<float>   mFrameTimeQueue;

        bool                mShowMainMenuBar;
        bool                mShowFrameInfoOverlay;
    };
}

#endif //SOLAR_GUI_H
