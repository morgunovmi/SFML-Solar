#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "frontend/Solar.h"

int main() {
    const auto width = 800;
    const auto height = 600;

    Solar system{ width, height };

    system.Run();

    return 0;
}
