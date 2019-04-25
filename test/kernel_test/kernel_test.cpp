﻿#include <iostream>

#include "wendland_kernel.hpp"
#include "cubic_spline.hpp"

int main()
{
    std::ios_base::sync_with_stdio(false);

    constexpr int n_max = 10000;

    std::cout << "compare dw(x) to (w(x + dx/2) - w(x - dx/2)) / dx\n" << std::endl;

    // spline
    {
        std::cout << "cubic spline" << std::endl;
        sph::Spline::Cubic cs;

        for(int n = 100; n < n_max; n *= 2) {
            const real dx = 1.0 / n;
            real error = 0.0;
            for(real x = dx * 0.5; x < 1.0; x += dx) {
                const vec_t r(x);
                auto dw1 = cs.dw(r, x, 1.0);
                auto dw2 = (cs.w(x + dx * 0.5, 1.0) - cs.w(x - dx * 0.5, 1.0)) / dx;
                error += std::abs(dw1[0] - dw2);
            }
            error /= n;
            std::cout << "error (n = " << n << "): " << error << std::endl;
        }
    }

    std::cout << std::endl;

    // wendland
    {
        std::cout << "Wendland C4" << std::endl;
        sph::Wendland::C4Kernel wl;

        for(int n = 100; n < n_max; n *= 2) {
            const real dx = 1.0 / n;
            real error = 0.0;
            for(real x = dx * 0.5; x < 1.0; x += dx) {
                const vec_t r(x);
                auto dw1 = wl.dw(r, x, 1.0);
                auto dw2 = (wl.w(x + dx * 0.5, 1.0) - wl.w(x - dx * 0.5, 1.0)) / dx;
                error += std::abs(dw1[0] - dw2);
            }
            error /= n;
            std::cout << "error (n = " << n << "): " << error << std::endl;
        }
    }

    return 0;
}
