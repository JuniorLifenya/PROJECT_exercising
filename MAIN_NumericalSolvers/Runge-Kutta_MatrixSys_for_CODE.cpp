#include <iostream>
#include <vector>
#include <cmath>

// Declaration of functions
double f(const double &t, const double &x, const double &y);
double g(const double &t, const double &x, const double &y);
void Runge_Kutta(std::vector<double> &x, std::vector<double> &y, std::vector<double> &t, const double &h, const int &n);
void printVector(std::vector<double> &v);

int main()
{
    // This code solves a system of ordinary differential equations using the Runge-Kutta method.
    // For systems like this one here :
    // dx/dt = f(t,x,y,z) = x + 2 * y
    // dy/dt = g(t,x,y,z) = 3*x+2*y
    int n;
    std::cout << "Please enter the # of iterations:" << std::endl;
    std::cin >> n;

    std::vector<double> t(n + 1); // Can also be written more compactely as std:: vector<double> t(n),x(n),y(n);
    std::vector<double> x(n + 1);
    std::vector<double> y(n + 1);
    double h = 0.02;

    t[0] = 0;
    x[0] = 6;
    y[0] = 4;

    Runge_Kutta(x, y, t, h, n);

    std::cout << "t= ";
    printVector(t);
    std::cout << "x= ";
    printVector(x);
    std::cout << "y= ";
    printVector(y);

    return 0;
}

// Now lets try the problem with dydx=(sin(x)-5y^2)/3 and conditions: y(0.3) = 5 . Checking if y(0.9)= -1261.5
// Definition of functions
double f(const double &t, const double &x, const double &y)
{
    return x + 2 * y;
}

double g(const double &t, const double &x, const double &y)
{

    return 3 * x + 2 * y;
}

void Runge_Kutta(std::vector<double> &x, std::vector<double> &y, std::vector<double> &t, const double &h, const int &n)
{
    for (int i = 0; i < n - 1; i++)
    {
        double K1 = f(t[i], x[i], y[i]);
        double G1 = g(t[i], x[i], y[i]);

        double K2 = f(t[i] + h / 2., x[i] + h / 2. * K1, y[i] + h / 2. * G1);
        double G2 = g(t[i] + h / 2., x[i] + h / 2. * K1, y[i] + h / 2. * G1);

        double K3 = f(t[i] + h / 2., x[i] + h / 2. * K2, y[i] + h / 2. * G2);
        double G3 = g(t[i] + h / 2., x[i] + h / 2. * K2, y[i] + h / 2. * G2);

        double K4 = f(t[i] + h, x[i] + h * K3, y[i] + h * G3);
        double G4 = g(t[i] + h, x[i] + h * K3, y[i] + h * G3);

        x[i + 1] = x[i] + h / 6. * (K1 + 2 * K2 + 2 * K3 + K4);
        y[i + 1] = y[i] + h / 6. * (G1 + 2 * G2 + 2 * G3 + G4);
        t[i + 1] = t[i] + h;
    }
}

void printVector(std::vector<double> &v)
{
    std::cout << "[";
    for (double element : v)
    {
        std::cout << element << ",";
    }
    std::cout << "]" << std::endl;
}

// Source for this code is mainly a comprehensive youtube video, GeeksforGeeks and Stackoverflow.
// Code execution here : g++ -std=c++11 -I eigen Runge-Kutta_MatrixSys_for_CODE.cpp -o lol output:
//