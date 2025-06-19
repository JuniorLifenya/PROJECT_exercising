// Now we can save the first 4 eigenvalues for different λ values
// and plot them using ROOT
int main()
{

    int I = 501;
    double xmin = -5.0, xmax = 5.0;
    vector<double> lambdas = {0.0, 0.1, 0.2, 0.5};
    fs::create_directories("data_files");

    ofstream specOut("data_files/eigenvalues_spectrum.txt");
    for (double L : lambdas)
    {
        auto H = Build_Hamiltonian(I, L); // Build Hamiltonian for each λ
        // Diagonalize the Hamiltonian
        SelfAdjointEigenSolver<MatrixXd> solver(H); // This is a faster way to diagonialize the Hamiltonian
        if (solver.info() != Success)
        {
            cerr << "Eigenvalue computation failed for λ = " << L << "!" << endl;
            continue; // Skip this λ if computation failed
        }
        auto E = solver.eigenvalues();

        // λ, E0, E1, E2, E3, …
        specOut << L;
        for (int n = 0; n < 4; ++n)
            specOut << " " << E[n];
        specOut << "\n";
    }
    specOut.close();
}