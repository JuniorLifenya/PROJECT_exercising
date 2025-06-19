#include "TFile.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"
#include <vector>
#include <Eigen/Dense> // for MatrixXd, VectorXd, etc.
#include <Eigen/Eigenvalues>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem> // Will be used for creating files and sending stuff to files

namespace fs = std::filesystem;
using namespace std;
using namespace Eigen;
MatrixXd Build_Hamiltonian(int N, double lambda) // This code was really built in the Hamiltonian_FDM_Buid.cpp file,
// but we will use it here to build the Hamiltonian matrix for the 1D anharmonic oscillator
{
    MatrixXd H = MatrixXd::Zero(N, N);       // Initialize the Hamiltonian matrix
    double dx = 0.1;                         // Spatial step size
    double hbar = 1.0, m = 1.0, omega = 1.0; // Constants for the harmonic oscillator

    // Now kinetic energy term
    double kin = hbar * hbar / (2 * m * dx * dx); // Kinetic energy term, trick from finite difference method
    for (int i = 0; i < N; i++)
    {
        H(i, i) = 2 * kin; // Diagonal elements
        if (i > 0)
            H(i, i - 1) = -kin; // Off-diagonal elements
        if (i < N - 1)
            H(i, i + 1) = -kin; // Off-diagonal elements
    }

    // The anharmonic potential: V(x) = ½mω²x² + lambda*x⁴
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
    MatrixXd H = Build_Hamiltonian(N, lambda); // Just like practiced in the Trytrain_for_understanding folder
    SelfAdjointEigenSolver<MatrixXd> solver(H);
    if (solver.info() != Success)
    {
        cerr << "Eigenvalue computation failed!" << endl; //  Cerr is for some error messages
        return 1;
    }

    // Get eigenvalues and eigenvectors from the solver(H) really
    VectorXd energies = solver.eigenvalues(); // Eigenvalues/energies of the system stored in a vector
    MatrixXd waves = solver.eigenvectors();   // Eigenvectors/functions/wavefunctions of the system stored in a matrix

    // Output first 5 eigenvalues
    cout << "First 5 eigenvalues (λ = " << lambda << "):\n"; // For our case λ = 0.0
    cout << "Index\tEnergy\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "E_" << i << " = " << energies(i) << endl;
    }

    // Compare with analytical harmonic oscillator
    cout << "\nComparison with analytical (harmonic oscillator):\n";
    for (int n = 0; n < 5; n++)
    {
        double expected = 0.5 + n; // ħω = 1, from E_n = (n + 1/2)ħω
        double computed = energies(n);
        cout << "n=" << n << ": computed=" << computed
             << ", expected=" << expected
             << ", error=" << abs(computed - expected) << endl; // Simple error estimate
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    // Save wavefunctions and energies to output file for visualization
    fs::create_directories("output");
    ofstream out("output/wavefunctions.dat");
    for (int i = 0; i < N; i++)
    {
        out << (i - N / 2.0) * 0.1 << " "; // Position in the grid in the center
        for (int j = 0; j <= 5; j++)       // Save first 5(included) wavefunctions
        {
            out << waves(i, j) << " "; // Real part of wavefunction
        }
        out << endl; // New line for next position
    }
    out.close();

    // Save energies to file
    ofstream energy_out("output/energies.dat"); // The dat file store the values but decoded so you can read it
    for (int i = 0; i < energies.size(); i++)
    {
        energy_out << i << " " << energies(i) << endl; // Index and energy
    }
    energy_out.close();
    cout << "\nWavefunctions and energies saved to 'wavefunctions.dat' and 'energies.dat' inside 'OUTPUT' folder." << endl;

    ///////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////

    // Now we can plot the eigenvalues for different λ values using ROOT, and send info to Root_Plot folder
    fs::create_directories("OUTPUT");                              // Create directory(AKA folder) for ROOT plots and stuff
    vector<double> lambda_values = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5}; // Use these λ values for the plot

    vector<TGraph *> graphs(5); // For first 5(included) eigenstates
    for (int i = 0; i < 5; i++)
    {
        graphs[i] = new TGraph(); // Create a new TGraph for each eigenstate
        graphs[i]->SetTitle(Form("Eigenstate %d", i));
        graphs[i]->GetXaxis()->SetTitle("Lambda");
        graphs[i]->GetYaxis()->SetTitle("Energy");
    }

    for (double lambda : lambda_values) // Loop over different λ values
    {
        MatrixXd H = Build_Hamiltonian(201, lambda); // Use odd N for symmetric grid
        // Diagonalize the Hamiltonian (again easier to work with because of non-complex eigenvalues)
        // For how it would have been done with complex matrix/eigenvalues see Trytrain_for_understanding folder
        SelfAdjointEigenSolver<MatrixXd> solver(H);
        VectorXd energies = solver.eigenvalues();

        for (int n = 0; n < 5; n++)
        {
            graphs[n]->SetPoint(graphs[n]->GetN(), lambda, energies(n));
        }
    }

    // Save to ROOT file
    TFile outfile("OUTPUT/eigenvalues.root", "RECREATE");
    for (int n = 0; n < 5; n++)
    {
        graphs[n]->Write(Form("energy_level_%d", n));
    }
    outfile.Close();
    cout << "Eigenvalues saved to 'eigenvalues.root'." << endl;
    // Clean up
    for (int i = 0; i < 5; i++)
    {
        delete graphs[i];
    }

    return 0;
}
// Most parts of this code are based on the Hamiltonian_Eigensolver folder, and the rest of the code is based on the Trytrain_for_understanding folder
// The code is designed to be run in a C++17 environment with the Eigen library and ROOT installed. Also some parts are from the internett.