#ifndef SOLAR_GUI_H
#define SOLAR_GUI_H

#include <queue>

#include <SFML/Graphics.hpp>

#include "misc/Log.h"

namespace slr {
    const uint16_t FRAME_QUEUE_SIZE = 60;

    class GUI {
    public:
        GUI(sf::RenderWindow& window, sf::Time& dt, Log& appLog) : mWindow(window), mDt(dt),
            mFrameTimeQueue(), mAppLog(appLog),
            mShowMainMenuBar(false), mShowFrameInfoOverlay(false), mShowAppLog(true) {}

        bool Init();

        void Update();

        void Render();

        void Shutdown();

    private:
        void PollEvents();

        void ShowMainMenuBar();
        void ShowFrameInfoOverlay();
        void ShowAppLog();

    private:
        sf::RenderWindow&   mWindow;
        sf::Time&           mDt;

        std::queue<float>   mFrameTimeQueue;

        Log&                mAppLog;

        bool                mShowMainMenuBar;
        bool                mShowFrameInfoOverlay;
        bool                mShowAppLog;
    };
}

#endif //SOLAR_GUI_H
