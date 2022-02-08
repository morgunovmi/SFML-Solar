#include <cstdint>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class Solar {
    public:
        Solar(uint16_t width, uint16_t height) :
            mWindowWidth(width), mWindowHeight(height),
            mWindow(sf::VideoMode{ width, height }, "Solar System", sf::Style::Close),
            mView(sf::FloatRect{ 0, 0, static_cast<float>(width), static_cast<float>(height) }),
            mCircle(100.f) {
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

        sf::CircleShape     mCircle;
        sf::Clock           mDeltaClock;

        const float         VIEW_MOVE_AMOUNT = 10.f;
        const float         VIEW_ZOOM_FACTOR = 1.2f;
};
