#ifndef SOLAR_RKSOLVER_H
#define SOLAR_RKSOLVER_H

#include <array>
#include <algorithm>

#include "Solver.h"

template<int Dim>
class RKSolver : public Solver<Dim> {
public:
    static constexpr stateArray<Dim> Solve(const stateArray<Dim>& init, float dt, auto rhsFunc)  {
        std::array<std::array<float, Dim * 2>, 4> koeffs{};

        // k1
        koeffs[0] = rhsFunc(init);

        // k2
        std::array<float, Dim * 2> init1{};
        std::transform(begin(init), end(init), begin(koeffs[0]), begin(init1),
                       [=](auto lhs, auto rhs){ return lhs + dt / 2 * rhs; });
        koeffs[1] = rhsFunc(init1);
        std::transform(begin(koeffs[1]), end(koeffs[1]), begin(koeffs[1]), [](auto val){ return 2 * val; });

        //k3
        std::array<float, Dim * 2> init2{};
        std::transform(begin(init), end(init), begin(koeffs[1]), begin(init2),
                       [=](auto lhs, auto rhs){ return lhs + dt / 2 * rhs; });
        koeffs[2] = rhsFunc(init2);
        std::transform(begin(koeffs[2]), end(koeffs[2]), begin(koeffs[2]), [](auto val){ return 2 * val; });

        //k4
        std::array<float, Dim * 2> init3{};
        std::transform(begin(init), end(init), begin(koeffs[2]), begin(init3),
                       [=](auto lhs, auto rhs){ return lhs + dt * rhs; });
        koeffs[3] = rhsFunc(init3);

        std::array<float, Dim * 2> ret{};
        for (size_t i = 0; i < Dim * 2; i++) {
            ret[i] = init[i] + 1.f / 6 * dt * (koeffs[0][i] + koeffs[1][i] + koeffs[2][i] + koeffs[3][i]);
        }
        return ret;
    }
};

#endif //SOLAR_RKSOLVER_H
