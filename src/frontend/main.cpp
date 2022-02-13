#include "frontend/Solar.h"
#include "physics/SolverTest.h"

int main() {
    //TestSolvers();

    const auto width = 800;
    const auto height = 600;

    slr::Solar system{ width, height };
    system.Run();

    return EXIT_SUCCESS;
}
