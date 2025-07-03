#include <vector>
#include <complex>
#include <cmath>
#include <fstream>
using namespace std;

using Complex = complex<double>;
using Matrix = vector<vector<Complex>>;

// SET YOUR N (Hilbert space dim)
int N = 10;

// Define dummy rho
Matrix rho(N, vector<Complex>(N, {0.0, 0.0}));

// Temporary definition
double wignerFUNC_combo(double x, double p, const Matrix &rho)
{
    return exp(-(x * x + p * p)); // just a Gaussian for now
}

int main()
{
    double hbar = 1.0;
    double x_min = -5.0, x_max = 5.0;
    double p_min = -5.0, p_max = 5.0;
    int N_grid = 100;

    ofstream file("PHASE_SPACE_stuff/wigner_data.csv");

    for (int i = 0; i < N_grid; ++i)
    {
        double x = x_min + i * (x_max - x_min) / (N_grid - 1);
        for (int j = 0; j < N_grid; ++j)
        {
            double p = p_min + j * (p_max - p_min) / (N_grid - 1);

            double W = wignerFUNC_combo(x, p, rho);
            file << x << "," << p << "," << W << "\n";
        }
    }
    file.close();
    return 0;
}

// No argument function added here :
void wignerFUNC_combo()
{
    int N = 10;
    Matrix rho(N, vector<Complex>(N, {0.0, 0.0}));

    double x_min = -5.0, x_max = 5.0;
    double p_min = -5.0, p_max = 5.0;
    int N_grid = 100;

    ofstream file("PHASE_SPACE_stuff/wigner_data.csv");

    for (int i = 0; i < N_grid; ++i)
    {
        double x = x_min + i * (x_max - x_min) / (N_grid - 1);
        for (int j = 0; j < N_grid; ++j)
        {
            double p = p_min + j * (p_max - p_min) / (N_grid - 1);
            double W = wignerFUNC_combo(x, p, rho);
            file << x << "," << p << "," << W << "\n";
        }
    }

    file.close();
}
