#include "physics/RKSolver.h"
#include "physics/ExplEulerSolver.h"
#include "physics/SolverTest.h"

#include <array>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xview.hpp>
#include <sciplot/sciplot.hpp>

using namespace sciplot;

// y'' - y' + 3y = t
// y(0) = 1
// y'(0) = -2
// t = [0, 4]

// y'' + y = 0
// y(0) = 1
// y'(0) = 1
// yex = sin(t) + cos(t)
// t = [0, 4]

int TestSolvers() {
    auto dxdy = [](auto t, auto y){ return std::array<float, 2>{y[1], t + y[1] - 3 * y[0]}; };
    auto h = 0.1f;

    auto t = xt::eval(xt::arange(0.f, 4.f + h, h));
    auto y = xt::eval(xt::zeros<float>({static_cast<size_t>(2), t.size()}));

    xt::col(y, 0) = xt::xarray<float>{1.f, -2.f};

    auto y_rk = y;
    auto y_simp = y;

    for (std::size_t i = 0; i < t.size() - 1; i++) {
        auto s = dxdy(t[i], std::array<float, 2>{xt::col(y_simp, i)[0], xt::col(y_simp, i)[1]});
        xt::col(y_simp, i + 1) = xt::col(y_simp, i) + h * xt::xarray<float>{s[0], s[1]};
    }

    for (std::size_t i = 0; i < t.size() - 1; i++) {
        const auto res = ExplEulerSolver<1>::Solve(t(i),
                                                   {xt::col(y, i)[0], xt::col(y, i)[1]}, h, dxdy);

        xt::col(y, i + 1) = xt::xarray<float>{res[0], res[1]};
    }

    for (std::size_t i = 0; i < t.size() - 1; i++) {
        const auto res = RKSolver<1>::Solve(t(i),
                                                   {xt::col(y_rk, i)[0], xt::col(y_rk, i)[1]}, h, dxdy);

        xt::col(y_rk, i + 1) = xt::xarray<float>{res[0], res[1]};
    }

    std::cout << t << '\n';
    std::cout << xt::row(y_rk, 0) << '\n';

    // Create a Plot object
    Plot plot{};

    // Set color palette
    plot.palette("set2");
    plot.drawCurve(t, xt::view(y, 0, xt::all())).label("Euler");
    plot.drawCurve(t, xt::view(y_simp, 0, xt::all())).label("simple");
    plot.drawCurve(t, xt::view(y_rk, 0, xt::all())).label("RK45");

    plot.show();

    return 0;
}