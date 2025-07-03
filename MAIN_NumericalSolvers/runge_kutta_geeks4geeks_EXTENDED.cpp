#include <iostream>
#include <cmath>
#include <vector>
using real = double;

// Derivative for solving like dy/dx = (sin x - 5 y^2)/3
real dydx(real x, real y)
{
    return (std::sin(x) - 5.0 * y * y) / 3.0;
}

// Single‐step scalar RK4 from x0→xf
real rungeKuttaScalar(real x0, real y0, real xf, real h)
{
    int n = int((xf - x0) / h); // should be 2
    real y = y0;
    for (int i = 0; i < n; i++)
    {
        real k1 = h * dydx(x0, y);
        real k2 = h * dydx(x0 + 0.5 * h, y + 0.5 * k1);
        real k3 = h * dydx(x0 + 0.5 * h, y + 0.5 * k2);
        real k4 = h * dydx(x0 + h, y + k3);
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        x0 += h;
    }
    return y;
}

// Vector‐based RK4 storing t[0…n], y[0…n]
void rungeKuttaVector(std::vector<real> &t,
                      std::vector<real> &y,
                      real x0, real y0, real h, int n)
{
    t[0] = x0;
    y[0] = y0;
    for (int i = 0; i < n; i++)
    {
        real ti = t[i], yi = y[i];
        real K1 = dydx(ti, yi);
        real K2 = dydx(ti + 0.5 * h, yi + 0.5 * h * K1);
        real K3 = dydx(ti + 0.5 * h, yi + 0.5 * h * K2);
        real K4 = dydx(ti + h, yi + h * K3);
        y[i + 1] = yi + h * (K1 + 2 * K2 + 2 * K3 + K4) / 6.0;
        t[i + 1] = ti + h;
    }
}

int main()
{
    real x0 = 0.3, y0 = 5.0, xf = 0.9, h = 0.3;
    int n = int((xf - x0) / h); // 2 steps

    // — Scalar call —
    real y_scalar = rungeKuttaScalar(x0, y0, xf, h);
    std::cout << "Scalar RK4: y(0.9) = " << y_scalar << "\n";

    // — Vector call —
    std::vector<real> t(n + 1), y(n + 1);
    rungeKuttaVector(t, y, x0, y0, h, n);
    std::cout << "Vector RK4: y(0.9) = " << y[n] << "\n";

    return 0;
}
// Expected output:
// Scalar RK4: y(0.9) = -1261.5
// Code execution CT_exercising/MAIN_NumericalSolvers$ g++ -std=c++11 -I eigen runge_kutta_geeks4geeks_EXTENDED.cpp -o lol, then type : ./lol
