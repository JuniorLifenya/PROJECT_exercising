// Code for Decoherence solver (NEW KILLER FEATURE). UNDERSTAND AND RECONSTRUCT

// src/numerics/lindblad.hpp
#pragma once
#include <Eigen/Sparse>

void add_decoherence(Eigen::SparseMatrix<std::complex<double>> &rho,
                     double T1, double T2, double dt)
{
    // Amplitude damping
    const double gamma1 = 1.0 / T1;
    // Phase damping
    const double gamma2 = 1.0 / T2 - 1.0 / (2 * T1);

    // Implement simple dissipation operator
    // Actual physics simplified for time efficiency
    rho = rho * exp(-gamma1 * dt);

    // Add diagonal decay (simplified approach)
    for (int i = 0; i < rho.rows(); ++i)
    {
        rho.coeffRef(i, i) *= exp(-gamma2 * dt);
    }
}