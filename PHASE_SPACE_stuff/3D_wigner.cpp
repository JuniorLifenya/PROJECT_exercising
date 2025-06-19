// 3D_wigner_fixed.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TTree.h>
#include <TH3.h>
#include <TCanvas.h>
#include <TString.h>
#include <TSystem.h>
#include <algorithm> // for min/max elements

void _3D_wigner()
{
    // Open wavefunction file
    std::ifstream infile("OUTPUT/wavefunctions.dat");
    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open wavefunction.dat" << std::endl;
        return;
    }

    // Vectors to store data
    std::vector<Double_t> x_vals, real_vals, imag_vals;

    // Parse file line by line
    std::string line;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        Double_t x, dummy, real, imag;

        // Read all 7 values but only use x and last two as real/imag
        if (iss >> x >> dummy >> dummy >> dummy >> dummy >> real >> imag)
        {
            // Use first value as x, last two as real/imag
            // Set y=0, z=0 since not provided
            x_vals.push_back(x);
            real_vals.push_back(real);
            imag_vals.push_back(imag);
        }
    }
    infile.close();

    size_t n = x_vals.size();
    TPolyMarker3D *marker = new TPolyMarker3D(n);

    double max_prob = 0;
    std::vector<double> probs(n);
    // Fill histogram
    for (size_t i = 0; i < n; i++)
    {
        Double_t prob = real_vals[i] * real_vals[i] + imag_vals[i] * imag_vals[i];
        probs[i] = prob;
        max_prob = std::max(max_prob, prob);
    }

    for (size_t i = 0; i < n; i++)
    {
        marker->SetPoint(i, x_vals[i], 0, 0);
        int color = TColor::GetColorPalette(int((probs[i] / max_prob) * 99)); // range 0-99
        marker->SetMarkerColor(color);
    }

    marker->SetMarkerSize(1.5);
    marker->SetMarkerStyle(20);

    TCanvas *c = new TCanvas("c", "Beautiful Wigner", 800, 600);
    marker->Draw();
    c->SaveAs("PHASE_SPACE_stuff/wigner_beautiful_3d.png");
}
