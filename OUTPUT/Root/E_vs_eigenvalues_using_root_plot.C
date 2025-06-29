#include <TFile.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <iostream>
#include <vector>
void E_vs_eigenvalues_using_root_plot()
{
    // Open the file that you created in C++
    TFile *f = TFile::Open("OUTPUT/eigenvalues.root");

    // Create a canvas and a multigraph to hold all levels
    TCanvas *c = new TCanvas("c", "Spectrum from ROOT file", 800, 600);
    TMultiGraph *mg = new TMultiGraph();

    const int nLevels = 5;
    for (int n = 0; n < nLevels; ++n)
    {
        // Read the graph written by the C++ script
        TGraph *g = (TGraph *)f->Get(Form("energy_level_%d", n));
        if (!g)
        {
            std::cerr << "Could not load graph energy_level_" << n << "\n";
            continue;
        }
        g->SetLineColor(n + 1);
        g->SetMarkerStyle(20 + n);
        g->SetTitle(Form("n = %d", n));
        mg->Add(g);
    }

    mg->SetTitle("Energy Levels vs Lambda (from ROOT file);Lambda;Energy");
    mg->Draw("APL");
    c->BuildLegend();
    c->SaveAs("OUTPUT/E_vs_eigenvalues_using_root.png");
}
