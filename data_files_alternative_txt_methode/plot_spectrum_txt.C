
// This is an alternative way to do the E_vs_eigenvalues_using_root_plot.C, with a txt file input
#include <TFile.h>
#include <TGraph.h>
#include <TCanvas.h>
void plot_spectrum_txt()
{
    const int nLevels = 4; // E0..E3
    vector<TGraph *> graphs(nLevels);
    for (int i = 0; i < nLevels; ++i)
        graphs[i] = new TGraph();

    ifstream fin("data_files/eigenvalues_spectrum.txt");
    double lambda, E[nLevels];

    while (fin >> lambda >> E[0] >> E[1] >> E[2] >> E[3])
    {
        for (int n = 0; n < nLevels; ++n)
            graphs[n]->SetPoint(graphs[n]->GetN(), lambda, E[n]);
    }

    TCanvas *c = new TCanvas("c", "Spectrum from TXT", 800, 600);
    TMultiGraph *mg = new TMultiGraph();

    for (int i = 0; i < nLevels; ++i)
    {
        graphs[i]->SetLineColor(i + 1);
        graphs[i]->SetMarkerStyle(20 + i);
        graphs[i]->SetTitle(Form("n = %d", i));
        mg->Add(graphs[i]);
    }

    mg->SetTitle("Energy Spectrum from TXT;Lambda;Energy");
    mg->Draw("APL");
    c->BuildLegend();
    c->SaveAs("output/spectrum_from_txt.png");
}
