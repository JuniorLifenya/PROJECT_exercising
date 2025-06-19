#include <TCanvas.h>
#include <TH2D.h>
#include <cmath>
#include <vector>

// Computes Wigner distribution for a quantum state
TH2D *compute_wigner(const std::vector<double> &wavefunction, double dx, double xmin)
{
    const int N = wavefunction.size();
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
                double y = y_idx * dx;
                int idx1 = (x_idx + y_idx) % N;     // Circular boundary
                int idx2 = (x_idx - y_idx + N) % N; // Circular boundary

                integral += wavefunction[idx1] * wavefunction[idx2] *
                            cos(2 * p * y / hbar) * dx;
            }
            wigner->Fill(x, p, integral / (M_PI * hbar));
        }
    }
    return wigner;
}

void wigner_calc_GroundState_analysis()
{
    // Parameters
    const int N = 100;        // Grid points
    const double dx = 0.1;    // Position step
    const double xmin = -5.0; // Minimum position

    // Create harmonic oscillator ground state
    std::vector<double> psi(N);
    for (int i = 0; i < N; i++)
    {
        double x = xmin + i * dx;
        psi[i] = exp(-x * x / 2.0) / pow(M_PI, 0.25); // Ground state
    }

    // Compute actual Wigner distribution
    TH2D *wigner = compute_wigner(psi, dx, xmin);

    // Create canvas with sufficient size

    TCanvas *canvas = new TCanvas("canvas", "Wigner Distribution", 1200, 900);
    canvas->SetRightMargin(0.15); // Space for color scale

    // Plot with nice color palette
    wigner->Draw("COLZ");
    wigner->SetMinimum(-0.1); // Show negative values
    wigner->SetMaximum(0.5);  // Adjust for visibility

    // Save output
    canvas->SaveAs("PHASE_SPACE_stuff/wigner_Ground_State_distribution.png");

    // Clean up
    delete wigner;
    delete canvas;
}