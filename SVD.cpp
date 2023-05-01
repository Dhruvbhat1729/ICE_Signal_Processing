#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>
#include <fstream>
#include <random>
using namespace std;
using namespace Eigen;

const double PI = 3.14159265358979323846;

int main()
{
    double fs = 1000; // Sampling frequency
    double f1 = 50; // Frequency of sinusoid 1
    double f2 = 75; // Frequency of sinusoid 2
    double f3 = 100; // Frequency of sinusoid 3
    double duration = 0.2; // Duration of signal in seconds
    double amplitude = 1; // Amplitude of each sinusoid
    int n_samples = fs * duration; // Number of samples in signal

    // Generate signal as a mixture of sinusoids
    double *signal = new double[n_samples]; // Allocate memory for signal
    for (int i = 0; i < n_samples; i++)
    {
        signal[i] = amplitude * (sin(2 * PI * f1 * i / fs) + sin(2 * PI * f2 * i / fs) + sin(2 * PI * f3 * i / fs));
    }
    
    // // Generate white noise with RMS power of -20 dBm
    double noise_rms = std::sqrt(1e-3 * pow(10, -20 / 10)); // RMS amplitude of noise signal
    std::default_random_engine generator; // Random number generator
    std::normal_distribution<double> distribution(0.0, noise_rms); // Normal distribution with given RMS amplitude
    double *noise = new double[n_samples]; // Allocate memory for noise signal

    for (int i = 0; i < n_samples; i++)
    {
        noise[i] = distribution(generator);
    }

    // Add noise to signal
    for (int i = 0; i < n_samples; i++)
    {
        signal[i] += noise[i];
    }

    // Save original signal without noise to file
    std::ofstream outfile("orignal_signals.txt");
    cout << "Oringal Signals without noise\n";
    for (int i = 0; i < n_samples; i++)
    {
        std::cout << signal[i] << endl;
        outfile << signal[i] << " ";
    }
  outfile.close();

    // Save original signal with noise to the file
    std::ofstream outfile2("orignal_signals_with_noise.txt");
    cout << "Oringal Signals with noise\n";
    for (int i = 0; i < n_samples; i++)
    {
        std::cout << signal[i] << std::endl;
        outfile2 << signal[i] << " ";
    }
    outfile2.close();

    int size = n_samples;
    std::vector<double> vec(signal, signal + size);
  
    // Define a noisy signal vector x
    vector<double> x = vec;
 
    // Create a matrix X with the signal values in the first column and zeros in the other columns
    MatrixXd X(x.size(), x.size());
    X.col(0) = Map<VectorXd>(x.data(), x.size());
    X.block(0, 1, x.size(), x.size() - 1) = MatrixXd::Zero(x.size(), x.size() - 1);

    // Compute the SVD of the matrix X
    JacobiSVD<MatrixXd> svd(X, ComputeThinU | ComputeThinV);

    // Extract the singular values and the left singular vectors
    VectorXd s = svd.singularValues();
    MatrixXd U = svd.matrixU();
    //cout<<s<<endl << s.size(); //cout<<s<<endl << s.size(); checking the matrix, python truncates all the small values on its own, hence error! C++ op
    
    // Choose a threshold value T to determine which singular values to keep
    double T = 0.1;

    // Set all singular values smaller than T to zero
    for (int i = 0; i < s.size(); i++)
    {
        if (s(i) < T)
        {
            s(i) = 0.0;
        }
    }
  
    // Sigma = s^2, hence the reconstructed signal needs to be multiplied by k
    double k = 1.0 / sqrt(n_samples);
  
    // Reconstruct the denoised signal by multiplying U and s with the transpose of the right singular vectors
    VectorXd y = k * U * s.asDiagonal() * U.transpose() * X.col(0);
  
    // Delete signals to prevent meamory leak
    delete[] signal;
    delete[] noise;

    std::ofstream outfile3("denoised.txt");
    cout << "Denoised signal: ";

    for (int i = 0; i < y.size(); i++)
    {
        cout << y(i) << " ";
        outfile3 << y(i) << " ";
    }

    outfile3.close();
    cout << endl;
    return 0;
}
