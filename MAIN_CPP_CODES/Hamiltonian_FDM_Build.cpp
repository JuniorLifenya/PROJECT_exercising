#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem> // Will be used for creating files and sending stuff to files

namespace fs = std::filesystem;
using namespace std;
using namespace Eigen;
MatrixXd Build_Hamiltonian(int N, double lambda) // Build the Hamiltonian using FDM
{
    MatrixXd H = MatrixXd::Zero(N, N);       // Initialize the Hamiltonian matrix
    double dx = 0.1;                         // Spatial step size
    double hbar = 1.0, m = 1.0, omega = 1.0; // Constants for the harmonic oscillator

    // Now kinetic energy term
    double kin = hbar * hbar / (2 * m * dx * dx); // Kinetic energy term
    for (int i = 0; i < N; i++)
    {
        H(i, i) = 2 * kin; // Diagonal elements
        if (i > 0)
            H(i, i - 1) = -kin; // Off-diagonal elements
        if (i < N - 1)
            H(i, i + 1) = -kin; // Off-diagonal elements
    }

    // Add anharmonic potential: V(x) = ½mω²x² + λx⁴
    for (int i = 0; i < N; i++)
    {
        double x = (i - N / 2.0) * dx;                                       // Position in the grid so center at x=0
        H(i, i) += 0.5 * m * omega * omega * x * x + lambda * x * x * x * x; // Harmonic potential term
    }
    return H; // Return the Hamiltonian matrix
}

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

// Now we Test the code
int main()
{
    // First we test and compare the Hamiltonian matrix for the 1D harmonic oscillator
    // Parameters needed for the Hamltonian matrix
    int N = 201;         // Grid points (odd number for symmetry)
    double lambda = 0.0; // Start with harmonic case

    // Build and diagonalize Hamiltonian
    MatrixXd H = Build_Hamiltonian(N, lambda); // Just like making matrices in Trytrain_for_understanding folder
    SelfAdjointEigenSolver<MatrixXd> solver(H);
    if (solver.info() != Success)
    {
        cerr << "Eigenvalue computation failed!" << endl;
        return 1;
    }

    // Get eigenvalues(energies) and eigenvectors(waves) from the solver(H)
    VectorXd energies = solver.eigenvalues();
    MatrixXd waves = solver.eigenvectors();

    // Output first 5 eigenvalues
    cout << "First 5 eigenvalues (λ = " << lambda << "):\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "E_" << i << " = " << energies(i) << endl;
    }

    // Compare with analytical harmonic oscillator
    cout << "\nComparison with analytical (harmonic oscillator):\n";
    for (int n = 0; n < 5; n++)
    {
        double expected = 0.5 + n; // ħω = 1
        double computed = energies(n);
        cout << "n=" << n << ": computed=" << computed
             << ", expected=" << expected
             << ", error=" << abs(computed - expected) << endl;
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    // So far This code builds a Hamiltonian matrix for a quantum harmonic oscillator with an anharmonic term,
    // diagonalizes it to find eigenvalues and eigenvectors, and saves the results for further analysis.
    // It uses the Eigen library for matrix operations and linear algebra.
    // The Hamiltonian is built using finite difference method (FDM) and the results are compared with analytical solutions.
    // I still get error before running the code about line 45 , which is the line with the Hamiltonian matrix declaration.
    // Also now we can dump all the outputs to a file that will be used for plotting and comparing later:

    int I = 501;
    double xmin = -5.0, xmax = 5.0;
    vector<double> lambdas = {0.0, 0.1, 0.2, 0.5};

    ofstream specOut("data_files/eigenvalues_spectrum.txt");
    for (double L : lambdas)
    {
        auto H = Build_Hamiltonian(I, L);
        SelfAdjointEigenSolver<MatrixXd> solver(H);
        auto E = solver.eigenvalues();

        // λ, E0, E1, E2, E3, …
        specOut << L;
        for (int n = 0; n < 4; ++n)
            specOut << " " << E[n];
        specOut << "\n";
    }
    specOut.close();
}