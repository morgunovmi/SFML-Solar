#include "frontend/Solar.h"

int main() {
    const auto width = 800;
    const auto height = 600;

    Solar system{ width, height };
    system.Run();

    return EXIT_SUCCESS;
}
