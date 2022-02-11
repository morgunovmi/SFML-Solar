#ifndef SOLAR_RKSOLVER_H
#define SOLAR_RKSOLVER_H

#include <array>
#include <algorithm>

template<int Dim, typename Func>
class RKSolver {
public:
    RKSolver() = default;

    static std::array<float, Dim * 2> Solve(const std::array<float, Dim * 2>& init, float dt, Func rhsFunc) {
        std::array<std::array<float, Dim * 2>, 4> koeffs{};

        koeffs[0] = rhsFunc(init);

        std::array<float, Dim * 2> init1{};
        for (std::size_t i = 0; i < Dim * 2; i++) {
            init1[i] = init[i] + dt / 2 * koeffs[0][i];
        }
        std::transform(init1.begin(), init1.end(), init1.begin(), [](float val){ return 2 * val; });
        koeffs[1] = rhsFunc(init1);

        std::array<float, Dim * 2> init2{};
        for (std::size_t i = 0; i < Dim * 2; i++) {
            init2[i] = init[i] + dt / 2 * koeffs[1][i];
        }
        std::transform(init2.begin(), init2.end(), init2.begin(), [](float val){ return 2 * val; });
        koeffs[2] = rhsFunc(init2);

        std::array<float, Dim * 2> init3{};
        for (std::size_t i = 0; i < Dim * 2; i++) {
            init2[i] = init[i] + dt * koeffs[1][i];
        }
        koeffs[3] = rhsFunc(init3);

        std::array<float, Dim * 2> ret{};
        for (size_t i = 0; i < Dim * 2; i++) {
            ret[i] = init[i] + 1.f / 6 * dt * (koeffs[0][i] + koeffs[1][i] + koeffs[2][i] + koeffs[3][i]);
        }
        return ret;
    }
};

#endif //SOLAR_RKSOLVER_H
