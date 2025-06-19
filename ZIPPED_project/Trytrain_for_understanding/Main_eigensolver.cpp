#define EIGEN_DONT_VECTORIZE
#define EIGEN_DONT_ALIGN

// This forces Eigen to compile with no SIMD optimizations or alignment tricks,
// avoiding that private‐member code path entirely.
#include <iostream>
#include <complex>
#include "eigen-3.4.0/Eigen/Dense" // Updated include path
#include "eigen-3.4.0/Eigen/Eigenvalues"
#include <iomanip>
#include <iostream> // For input and output operations
#include <vector>
#include <complex> // For complex number support
#include <iterator>
#include <Eigen/Dense> //Used for heacy matrix operations
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen; // This will help the task to be easier, as we can use MatrixXd... instead of Eigen::MatrixXd...

int main() // Here we use the main function as an entry point for our program.
// Note: The main function is the entry point of a C++ program.
{
     //////////////////////////////////////////////////////////////////////////
     /////////////////////////////////////////////////////////////////////////

     // Define  a specific matrix:
     MatrixXd MatA(3, 3);
     MatA << 1, 2, 3,
         4, 5, 6,
         7, 8, 9;
     // Print to check and exercise for understanding:
     cout << "This is my  well defined Matrix A:\n"
          << MatA << endl;
     cout << "\n";

     // Create a 3x3 random matrix
     MatrixXd randomMatA = MatrixXd::Random(3, 3);
     // Print it just to check:
     cout << "This is a random matrix A:\n"
          << randomMatA << endl;
     cout << "\n";

     ///////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////

     // Generate a symmetric matrix (if not already)
     MatrixXd randomMatB = MatrixXd::Random(3, 3);
     MatrixXd tempB = randomMatB;            // Create explicit copy
     randomMatB = tempB + tempB.transpose(); // Safe operation

     cout << "This is a random symmetric matrix B:\n"
          << randomMatB << endl;
     cout << "\n";

     /////////////////////////////////////////////////////////////////////
     ////////////////////////////////////////////////////////////////////

     // Now we can compute the real eigenvalues of a matrix
     EigenSolver<MatrixXd> eigensolver(randomMatB); // Using the symmetric matrix B
     if (eigensolver.info() != Success)
     {
          cout << "Eigenvalue computation failed!" << endl;
          return -1; // Exit with an error code
     }
     VectorXcd eigenvalues = eigensolver.eigenvalues();   // Get the eigenvalues
     MatrixXcd eigenvectors = eigensolver.eigenvectors(); // Get the eigenvectors
     // Print the results
     cout << "Real Eigenvalues from the random symmetric matrix B:\n"
          << eigenvalues << endl;
     cout << "\n"
          << "Real Eigenvectors from the random symmetric matrix B:\n"
          << eigenvectors << endl;
     cout << "\n";

     ///////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////

     // We can also work with matrix with complex values
     // Create a complex random matrix A
     MatrixXcd A(3, 3);
     A.real() = MatrixXd::Random(3, 3); // Real part
     A.imag() = MatrixXd::Random(3, 3); // Imaginary part
     // Alternatively, you can use:
     // MatrixXcd A = MatrixXcd::Random(3, 3); // This creates a random complex matrix directly but does not work for some reason

     // We want to work with a Hermitian version for simplicity and relation to physics observables: (A + A†)/2
     MatrixXcd HermitianA = (A + A.adjoint()) / 2.0; // Make it Hermitian

     // Print it to check:
     cout << "This a random complex matrix A: \n"
          << A << endl;
     cout << "\n";
     cout << "Real part of A:\n"
          << A.real() << endl;
     cout << "\n";
     cout << "Imaginary part of A:\n"
          << A.imag() << endl;

     cout << "\n";
     cout << "  This is the Hermitian version of the complex matrix A:\n"
          << HermitianA << endl;
     cout << "\n ";

     // This is important because the eigenvalues could be complex also

     ///////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////

     // Now we can compute the complex eigenvalues of a complex matrix
     ComplexEigenSolver<MatrixXcd> ces;
     ces.compute(MatA); // Using the complex matrix A
     if (ces.info() != Success)
     {
          cout << "Eigenvalue computation failed!" << endl;
          return -1; // Exit with an error code
     }
     VectorXcd Comp_eigenvalues = ces.eigenvalues();   // Get the eigenvalues
     MatrixXcd Comp_eigenvectors = ces.eigenvectors(); // Get the eigenvectors
     // Print the results
     cout << "Complex Eigenvalues from the random complex matrix:\n"
          << Comp_eigenvalues << endl;
     cout << "\n"
          << "Complex Eigenvectors from the random complex matrix:\n"
          << Comp_eigenvectors << endl;
     cout << "\n";

     ///////////////////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////////////////
     return 0;
}