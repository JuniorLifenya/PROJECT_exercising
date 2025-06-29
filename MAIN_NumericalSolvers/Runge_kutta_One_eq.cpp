// C++ program of the above approach
#include <iostream>
#include <cmath>

using namespace std;

// A sample differential equation "dy/dx = (x - y)/2"
double dydx(float x, float y)
{
    return (x - y) / (2);
}

// Finds value of y for a given x using step size h
// and initial value y0 at x0.
double rungeKutta(float x0, float y0, float xf, float h)
{
    // Count number of iterations using step size or
    // step height h
    double delta = (static_cast<double>((xf) - (x0)) / h);
    int n = static_cast<int>(round(delta));

    double k1,
        k2, k3, k4, k5;

    // Iterate for number of iterations
    double y = y0;
    for (int i = 1; i <= n; i++)
    {
        // Apply Runge Kutta Formulas to find
        // next value of y
        double k1 = h * dydx(x0, y);
        double k2 = h * dydx(x0 + 0.5 * h, y + 0.5 * k1);
        double k3 = h * dydx(x0 + 0.5 * h, y + 0.5 * k2);
        double k4 = h * dydx(x0 + h, y + k3);

        // Update next value of y
        y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        ;

        // Update next value of x
        x0 = x0 + h;
    }

    return y;
}

// Driver Code
int main()
{
    float x0 = 0, y0 = 1, xf = 2, h = 0.2;
    cout << "The value of y at x is : " << rungeKutta(x0, y0, xf, h);

    return 0;
}

// This code is contributed by code_hunt. Sources for information GeeksforGeeks.org
// Expected Output: The value of y at x is : 1.10364
