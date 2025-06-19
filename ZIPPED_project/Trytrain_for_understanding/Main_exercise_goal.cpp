
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// Add potential function to your eigenvalue solver
double anharmonic_potential(double x, double lambda)
{
    return 0.5 * x * x + lambda * x * x * x * x; // V(x) = ½x² + λx⁴
}

// In matrix construction loop:
for (int i = 0; i < N; i++)
{
    double x = x_min + i * dx;
    H(i, i) = kinetic_term + anharmonic_potential(x, lambda);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Add ROOT output to visualize eigenvalues:
// cpp

#include "TFile.h"
#include "TGraph.h"

// After eigenvalue calculation
TFile *file = new TFile("eigenvalues.root", "RECREATE");
TGraph *g = new TGraph();
for (int i = 0; i < num_eigenvalues; i++)
{
    g->SetPoint(i, lambda, eigenvalues(i).real());
}
g->Write("lambda_scan");
file->Close();

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
Day 2 : Wavefunction Visualization
            Extend eigenvalue code to save eigenvectors

                Create ROOT macro to plot wavefunctions :

    cpp
        // In your eigenvalue code
        std::ofstream out("wavefunctions.dat");
for (int i = 0; i < N; i++)
{
    out << x[i] << " " << eigenvectors.col(0)(i).real() << "\n";
}

// ROOT macro: plot_wavefunctions.C
void plot_wavefunctions()
{
    TGraph *g = new TGraph("wavefunctions.dat");
    g->SetTitle("Ground State Wavefunction;x;ψ(x)");
    g->Draw("AL");
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Day 3 : Classical Phase - Space Analysis Modify your Runge - Kutta code :

    cpp
    // New ODE system for oscillator
    void
    derivatives(double t, const double *y, double *dydt)
{
    double x = y[0];
    double p = y[1];
    dydt[0] = p;                       // dx/dt = p
    dydt[1] = -x - lambda * x * x * x; // dp/dt = -dV/dx
}

// In output routine
std::ofstream traj("phase_space.dat");
traj << x << " " << p << "\n"; // Save position/momentu

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
Day 4: ROOT Visualization Suite
Create ROOT macros for:

Phase-space portraits (p vs x)

Energy conservation checks

Poincaré sections (stroboscopic sampling)

Example macro:

cpp
// phase_space.C
void phase_space()
{
    TGraph *g = new TGraph("phase_space.dat");
    g->SetTitle("Phase Space;x;p");
    g->Draw("AP");

    // Add harmonic oscillator reference
    TF1 *f = new TF1("f", "sqrt(1-x*x)", -1, 1);
    f->SetLineColor(kRed);
    f->Draw("same");
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Day 5 : Integration &Reporting
            Combine components into ROOT application :

    cpp
    // main_application.C
    void
    main_app(double lambda)
{
    // 1. Quantum calculation
    solve_eigenvalues(lambda);

    // 2. Classical simulation
    run_oscillator_simulation(lambda);

    // 3. Auto-generate reports
    gROOT->ProcessLine(".x plot_wavefunctions.C");
    gROOT->ProcessLine(".x phase_space.C");
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////