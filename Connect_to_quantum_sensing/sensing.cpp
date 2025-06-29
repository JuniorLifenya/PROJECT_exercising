

// Sensing Analysis Function, analyze and understand , reconstruct fully with time record.

void analyze_sensitivity(const std::vector<double> &frequencies,
                         const std::vector<double> &responses)
{
    // Simple linear regression (you already have the data)
    double sum_xy = 0, sum_x = 0, sum_y = 0, sum_x2 = 0;
    const int n = frequencies.size();

    for (int i = 0; i < n; i++)
    {
        sum_x += frequencies[i];
        sum_y += responses[i];
        sum_xy += frequencies[i] * responses[i];
        sum_x2 += frequencies[i] * frequencies[i];
    }

    const double slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    std::cout << "\n=== QUANTUM SENSING REPORT ===\n";
    std::cout << "Strain sensitivity: " << slope << " Hz/nanostrain\n";
    std::cout << "Theoretical limit: 1.5 Hz/nanostrain\n";
    std::cout << "==============================\n";

    // Add to your existing output
    std::ofstream report("sensitivity_report.txt");
    report << "Estimated strain sensitivity: " << slope << " Hz/nanostrain\n";
}