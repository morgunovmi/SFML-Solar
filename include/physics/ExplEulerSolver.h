#ifndef SOLAR_EXPLEULERSOLVER_H
#define SOLAR_EXPLEULERSOLVER_H

#include "Solver.h"

template<int Dim>
class ExplEulerSolver : public Solver<Dim> {
public:
    static constexpr stateArray<Dim> Solve(const stateArray <Dim>& init, float dt, auto rhsFunc) {
        const auto k = rhsFunc(init);

        stateArray<Dim> res{};
        std::transform(begin(init), end(init), begin(k), begin(res),
                       [=](auto lhs, auto rhs){ return lhs + dt * rhs; });

        return res;
    }
};

#endif //SOLAR_EXPLEULERSOLVER_H
