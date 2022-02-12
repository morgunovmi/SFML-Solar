#ifndef SOLAR_SOLVER_H
#define SOLAR_SOLVER_H

#include <array>

template<int Dim>
using stateArray = std::array<float, Dim * 2>;

template<int Dim>
class Solver {
public:
    Solver() = default;

    virtual ~Solver() = default;

    static constexpr stateArray<Dim> Solve(const stateArray<Dim>& init, float dt, auto func) {}
};

#endif //SOLAR_SOLVER_H
