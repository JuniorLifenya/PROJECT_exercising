// Now here for the output we have in wavefunctions.dat:
// We will compute the Wigner distribution in that case . We will use the
#include <TCanvas.h>
#include <TH2D.h>
#include <TGraph.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>

// Function to compute Wigner distribution
TH2D *compute_wigner(const std::vector<double> &psi, double dx, double xmin)
{
    const int N = psi.size();
    const double hbar = 1.0;
    const double dp = 2 * M_PI / (N * dx); // Momentum resolution

    // Create histogram for Wigner distribution
    TH2D *wigner = new TH2D("wigner", "Wigner Distribution;Position (x);Momentum (p)",
                            N, xmin, xmin + (N - 1) * dx,
                            N, -N * dp / 2, N * dp / 2);
    wigner->SetContour(100); // Smooth color gradient

    for (int x_idx = 0; x_idx < N; x_idx++)
    {
        double x = xmin + x_idx * dx;
        for (int p_idx = 0; p_idx < N; p_idx++)
        {
            double p = -N * dp / 2 + p_idx * dp;
            double integral = 0.0;

            // Compute Wigner integral
            for (int y_idx = 0; y_idx < N; y_idx++)
            {
                int idx1 = (x_idx + y_idx) % N;     // Circular boundary
                int idx2 = (x_idx - y_idx + N) % N; // Circular boundary
                double y = y_idx * dx;

                integral += psi[idx1] * psi[idx2] * cos(2 * p * y / hbar) * dx;
            }
            wigner->Fill(x, p, integral / (M_PI * hbar));
        }
    }
    return wigner;
}

void my_wigner_clalc()
{
    // Open your wavefunction data file
    std::ifstream file("output/wavefunctions.dat");
    if (!file.is_open())
    {
        std::cerr << "Error: Could not open wavefunctions.dat" << std::endl;
        return;
    }

    // Read data
    std::vector<double> x_values;
    std::vector<double> psi_ground;
    std::vector<double> psi_first_excited;

    double x, psi0, psi1;
    while (file >> x >> psi0 >> psi1)
    {
        x_values.push_back(x);
        psi_ground.push_back(psi0);
        psi_first_excited.push_back(psi1);
    }
    file.close();

    const int N = x_values.size();
    const double dx = fabs(x_values[1] - x_values[0]); // Calculate step size
    const double xmin = x_values[0];                   // First x-value

    // Compute Wigner for ground state
    TH2D *wigner_ground = compute_wigner(psi_ground, dx, xmin);

    // Create canvas
    TCanvas *canvas = new TCanvas("canvas", "Wigner Distributions", 1800, 900);
    canvas->Divide(2, 1);

    // Plot ground state
    canvas->cd(1);
    wigner_ground->SetTitle("Ground State Wigner Distribution;x; p");
    wigner_ground->Draw("COLZ");

    // Compute and plot first excited state
    canvas->cd(2);
    TH2D *wigner_excited = compute_wigner(psi_first_excited, dx, xmin);
    wigner_excited->SetTitle("First Excited State Wigner Distribution;x; p");
    wigner_excited->Draw("COLZ");

    // Save output
    canvas->SaveAs("PHASE_SPACE_stuff/my_wigner_comparison.png");

    // Clean up
    delete wigner_ground;
    delete wigner_excited;
    delete canvas;
}