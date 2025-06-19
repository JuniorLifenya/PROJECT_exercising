
void plot_wave_and_density()
{
    // 1) Open and skip headers
    std::ifstream fin("output/wavefunctions.dat");
    if (!fin)
    {
        std::cerr << "ERROR: cannot open output/wavefunctions.dat\n";
        return;
    }

    // 2) Prepare graphs
    const int nStates = 6;
    std::vector<TGraph *> wf(nStates), pd(nStates); // Wavefunctions and probability densities
    // Initialize graphs for each state
    for (int i = 0; i < nStates; i++)
    {
        wf[i] = new TGraph();
        pd[i] = new TGraph();
    }

    // 3) Read data
    double x, psi[nStates];
    while (fin >> x >> psi[0] >> psi[1] >> psi[2] >> psi[3] >> psi[4] >> psi[5])
    {
        for (int i = 0; i < nStates; i++)
        {
            wf[i]->SetPoint(wf[i]->GetN(), x, psi[i]);
            pd[i]->SetPoint(pd[i]->GetN(), x, psi[i] * psi[i]);
        }
    }
    fin.close();

    // 4) Plot wavefunctions
    TCanvas *c1 = new TCanvas("c1", "Wavefunctions", 800, 700); // Resolution for the output grid
    wf[0]->SetTitle("Wavefunctions (λ≃0.2);x;ψ_n(x)");
    wf[0]->Draw("AL");
    // e.g. domain [–10, +10]
    wf[0]->GetXaxis()->SetLimits(-5.5, +5.5);
    pd[0]->GetXaxis()->SetLimits(-5.5, +5.5);
    wf[0]->GetYaxis()->SetRangeUser(-.5, .5); // Adjust Y-axis range as needed
    wf[0]->GetYaxis()->SetTitle("Wavefunction ψ_n(x)");
    for (int i = 1; i < nStates; ++i)
    {
        wf[i]->SetLineColor(i + 1);
        wf[i]->Draw("L SAME");
    }
    c1->BuildLegend();
    c1->SaveAs("output/wavefunctions_plot_fixed.png");

    // 5) Plot probability densities
    TCanvas *c2 = new TCanvas("c2", "Probability Densities", 800, 700);
    pd[0]->SetTitle("Probability Densities (λ≃0.2);x;|ψ_n(x)|^{2}");
    pd[0]->Draw("AL");
    for (int i = 1; i < nStates; ++i)
    {
        pd[i]->SetLineColor(i + 1);
        pd[i]->Draw("L SAME");
    }
    c2->BuildLegend();
    c2->SaveAs("output/prob_densities_plot.png");

    // Clean up
    for (int i = 0; i < nStates; i++)
    {
        delete wf[i];
        delete pd[i];
    }
}
// Run only with root , not compiling with real g++ (gave me A lot of problems)
// do .L MAIN_CPP_CODES/plot_wave_and_density.C plot_wave_and_density()
