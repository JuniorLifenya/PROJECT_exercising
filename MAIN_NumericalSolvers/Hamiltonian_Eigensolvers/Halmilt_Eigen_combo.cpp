
// This code is really junk because it was an atempt to unify the different stuff i have created,
// so igore it because it is all in the Main.cpp file now

#include <Eigen/Eigenvalues>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <complex>

using namespace Eigen;
using namespace std;
int main()
{

    ///////////////////////////////////////////////////////////////////////////////////////
    // First add our Constructed Main eigensolver
    ///////////// This one gives real Eigenvalues/vectors /////////////////////////////////

    // Generate a symmetric matrix (if not already)
    MatrixXd randomMatB = MatrixXd::Random(3, 3);
    MatrixXd tempB = randomMatB;            // Create explicit copy
    randomMatB = tempB + tempB.transpose(); // Safe operation

    cout << "This is a random symmetric matrix B:\n"
         << randomMatB << endl;
    cout << "\n";

    EigenSolver<MatrixXd> eigensolver(randomMatB) // Using the symmetric matrix B
        if (eigensolver.info() != Success)
    {
        cout << "Eigenvalue computation failed!" << endl;
        return -1; // Exit with an error code
    }
    VectorXcd eigenvalues = eigensolver.eigenvalues();   // Get the eigenvalues
    MatrixXcd eigenvectors = eigensolver.eigenvectors(); // Get the eigenvectors

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////// This one gives complex Eigenvalues/vectors ///////////////////////////////

    // Create a random complex matrix A
    MatrixXcd A(3, 3);
    A.real() = MatrixXd::Random(3, 3); // Real part
    A.imag() = MatrixXd::Random(3, 3); // Imaginary part
    // Alternatively, you can use:
    // MatrixXcd A = MatrixXcd::Random(3, 3); // This creates a random complex matrix directly but does not work for some reason

    // We want to work with a Hermitian version for simplicity and relation to physics observables: (A + A†)/2
    MatrixXcd HermitianA = (A + A.adjoint()) / 2.0; // Make it Hermitian

    ComplexEigenSolver<MatrixXcd> ces;
    ces.compute(A); // Using the complex matrix A
    if (ces.info() != Success)
    {
        cout << "Eigenvalue computation failed!" << endl;
        return -1; // Exit with an error code
    }
    VectorXcd Comp_eigenvalues = ces.eigenvalues();   // Get the eigenvalues
    MatrixXcd Comp_eigenvectors = ces.eigenvectors(); // Get the eigenvectors

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    // Now we Build the Hamiltonian matrix for the 1D harmonic oscillator usin the FDM:
    // For 1D Hamiltonian for V(x)=½mω²x² + λx⁴

    MatrixXd Build_Hamiltonian(int N, double lambda, double xmin, double xmax)
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

        // Now add anharmonic potential term
        for (int i = 0; i < N; i++)
        {
            double x = (i - N / 2.0) * dx;                                       // Position in the grid
            H(i, i) += 0.5 * m * omega * omega * x * x + lambda * x * x * x * x; // Harmonic potential term
        }
        return H; // Return the Hamiltonian matrix
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    double lambda = 0.1;
    MatrixXd H = build_hamiltonian(100, lambda);
    SelfAdjointEigenSolver<MatrixXd> solver(H);
    VectorXd energies = solver.eigenvalues();
    MatrixXd waves = solver.eigenvectors();

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////
}
