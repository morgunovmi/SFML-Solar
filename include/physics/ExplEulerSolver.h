#ifndef SOLAR_EXPLEULERSOLVER_H
#define SOLAR_EXPLEULERSOLVER_H

#include "Solver.h"

#include <fmt/format.h>

template<int Dim>
class ExplEulerSolver : public Solver<Dim> {
public:
    [[nodiscard]] static constexpr stateArray<Dim> Solve(float t, const stateArray <Dim>& init, float dt, auto rhsFunc) {
        const auto k = rhsFunc(t, init);

        /*
        for (const auto val: k) {
            fmt::print("{} ", val);
        }
        fmt::print("\n");
         */

        stateArray<Dim> res{};
        std::transform(begin(init), end(init), begin(k), begin(res),
                       [=](auto lhs, auto rhs){ return lhs + dt * rhs; });

        return res;
    }
};

#endif //SOLAR_EXPLEULERSOLVER_H
