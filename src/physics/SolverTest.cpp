#include "physics/RKSolver.h"
#include "physics/ExplEulerSolver.h"
#include "physics/SolverTest.h"

#include <array>
#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>
#include <sciplot/sciplot.hpp>

using namespace sciplot;

// y'' - y' + 3y = t
// y(0) = 1
// y'(0) = -2
// t = [0, 4]

int TestSolvers() {
    auto dxdy = [](auto t, auto y){ return std::array<float, 2>{y[1], t + y[1] - y[0]}; };
    auto h = 0.1f;

    auto t = xt::eval(xt::arange(0.f, 4 + h, h));
    auto y = xt::eval(xt::zeros<float>({static_cast<size_t>(2), t.size()}));

    xt::col(y, 0) = xt::xarray<float>{1.f, -2.f};

    auto y_rk = y;

    for (std::size_t i = 0; i < t.size() - 1; i++) {
        const auto res = ExplEulerSolver<1>::Solve(t(i),
                                                   {xt::col(y, i)[0], xt::col(y, i)[1]}, h, dxdy);

        xt::col(y, i + 1) = xt::xarray<float>{res[0], res[1]};
    }

    for (auto val : xt::view(y_rk, 0, xt::all())) {
        std::cout << val << '\n';
    }

    for (std::size_t i = 0; i < t.size() - 1; i++) {
        const auto res = RKSolver<1>::Solve(t(i),
                                                   {xt::col(y_rk, i)[0], xt::col(y_rk, i)[1]}, h, dxdy);

        xt::col(y_rk, i + 1) = xt::xarray<float>{res[0], res[1]};
    }

    // Create a Plot object
    Plot plot{};

    // Set color palette
    plot.palette("set2");
    plot.drawPoints(t, xt::view(y, 0, xt::all())).label("Euler");
    plot.drawPoints(t, xt::view(y_rk, 0, xt::all())).label("RK45");

    plot.show();

    return 0;
}