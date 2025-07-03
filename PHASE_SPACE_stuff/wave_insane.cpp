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
#include <TMultiGraph.h>
#include <TGraph.h>
#include <TPolyLine3D.h>
#include <TColor.h>
#include <TROOT.h>
#include <TView.h>
#include <TLegend.h>
#include <algorithm>

void wave_insane()
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
            x_vals.push_back(x);
            real_vals.push_back(real);
            imag_vals.push_back(imag);
        }
    }
    infile.close();

    size_t n = x_vals.size();
    if (n == 0)
    {
        std::cerr << "Error: No valid data found!" << std::endl;
        return;
    }

    // Calculate probabilities and find maximum
    double max_prob = 0;
    std::vector<double> probs(n);
    for (size_t i = 0; i < n; i++)
    {
        probs[i] = real_vals[i] * real_vals[i] + imag_vals[i] * imag_vals[i];
        max_prob = std::max(max_prob, probs[i]);
    }

    // Create canvas with two pads
    TCanvas *c1 = new TCanvas("c1", "Wavefunction Visualization", 1200, 600);
    c1->Divide(2, 1);

    // Pad 1: 3D Visualization
    c1->cd(1);

    // Determine axis ranges
    double x_min = *std::min_element(x_vals.begin(), x_vals.end());
    double x_max = *std::max_element(x_vals.begin(), x_vals.end());
    double padding = (x_max - x_min) * 0.1;

    // Create 3D histogram for axis frame
    TH3F *frame = new TH3F("frame", "Probability Density along X-axis;X;Y;Z",
                           10, x_min - padding, x_max + padding,
                           10, -0.1, 0.1,
                           10, -0.1, 0.1);
    frame->SetStats(0);
    frame->GetXaxis()->CenterTitle();
    frame->GetYaxis()->CenterTitle();
    frame->GetZaxis()->CenterTitle();
    frame->Draw("AXIS");

    // Draw x-axis reference line
    TPolyLine3D *axis_line = new TPolyLine3D(2);
    axis_line->SetPoint(0, x_min, 0, 0);
    axis_line->SetPoint(1, x_max, 0, 0);
    axis_line->SetLineColor(kGray);
    axis_line->SetLineStyle(2);
    axis_line->Draw();

    // Create color palette
    gStyle->SetPalette(kRainBow);

    // Create and draw markers with color mapping
    TPolyMarker3D *marker = new TPolyMarker3D(n);
    for (size_t i = 0; i < n; i++)
    {
        marker->SetPoint(i, x_vals[i], 0, 0);
        double norm_prob = probs[i] / max_prob;
        int color_idx = TColor::GetColorPalette(static_cast<int>(norm_prob * 99));
        marker->SetMarkerColor(color_idx);
    }
    marker->SetMarkerSize(1.5);
    marker->SetMarkerStyle(20);
    marker->Draw();

    // Initialize 3D view properly
    TView *view = TView::CreateView(1);
    view->SetRange(x_min - padding, -0.1, -0.1, x_max + padding, 0.1, 0.1);
    view->ShowAxis();
    view->RotateView(30, 60); // Elevation, azimuth angles
    gPad->SetView(view);

    // Pad 2: 2D Wavefunction Components
    c1->cd(2);

    // Create multi-graph for components
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Wavefunction Components;X Position;Value");

    TGraph *gr_real = new TGraph(n, x_vals.data(), real_vals.data());
    gr_real->SetLineColor(kBlue);
    gr_real->SetTitle("Real Part");

    TGraph *gr_imag = new TGraph(n, x_vals.data(), imag_vals.data());
    gr_imag->SetLineColor(kRed);
    gr_imag->SetTitle("Imaginary Part");

    TGraph *gr_prob = new TGraph(n, x_vals.data(), probs.data());
    gr_prob->SetLineColor(kGreen + 2);
    gr_prob->SetTitle("Probability Density");

    mg->Add(gr_real);
    mg->Add(gr_imag);
    mg->Add(gr_prob);
    mg->Draw("AL");

    // Add legend
    TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.9);
    leg->AddEntry(gr_real, "Real Part", "l");
    leg->AddEntry(gr_imag, "Imaginary Part", "l");
    leg->AddEntry(gr_prob, "Probability Density", "l");
    leg->Draw();

    // Save combined plot
    c1->SaveAs("PHASE_SPACE_stuff/wave_insane.png");
}