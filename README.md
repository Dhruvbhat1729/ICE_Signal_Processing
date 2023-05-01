# ICE Software Challenge - Denoising using SVD

## Introduction to SVD
Singular Value Decomposition (SVD) of a matrix is a factorization of a matrix into three matrices. It has some interesting algebraic properties and conveys important geometrical and theoretical insights about linear transformations. In simple terms it is used to reduce the dimensionality of a large set of data while preserving the most important features of the original data. 

### Math behind SVD

<p>
  <img src = "https://github.com/Dhruvbhat1729/ICE_Online-Challenge/blob/main/Singulardecomposition-660x187.png" alt = "Math Formula" width = "40%" /> </br>
  
- U:  mxn matrix is the orthonormal eigenvectors of AA^{T}. </br>
- VT: transpose of a nxn matrix containing the orthonormal eigenvectors of A^{T}A. </br>
- W:  a nxn diagonal matrix of the singular values which are the square roots of the eigenvalues of A^{T}A.                                                        

## Algorithm for SVD 

1. First, represent the signal as a matrix X. The signal values are placed in the first column of X, and zeros are placed in the other columns. The size of the matrix is      NxN, where N is the number of samples in the signal.

2. Compute the SVD of X using a library like Eigen. The SVD decomposes X into three matrices: U, Σ, and V. U is an orthogonal matrix containing the left singular vectors, Σ    is a diagonal matrix containing the singular values, and V is an orthogonal matrix containing the right singular vectors.

3. Choose a threshold value T. All singular values smaller than T are set to zero. The idea is that small singular values correspond to noise in the signal and can be          safely removed.

4. Reconstruct the signal by multiplying U, Σ, and V' (the transpose of V) together. The reconstructed signal is obtained by multiplying U, the modified Σ, and V' together.

The reconstructed signal obtained from step 4 can now be considered as denoised.

## Software Requirements

- C++
- Python
- External library eigen 

## Set Up

### Setting up C++ for VS Code
Install VS Code </br>
Install [MinGW](https://osdn.net/projects/mingw/releases/) or [MinGW-w64](http://mingw-w64.org/doku.php) or [TDM gcc](https://jmeubank.github.io/tdm-gcc/) </br>  
Follow this video for easy [installation](https://www.youtube.com/watch?v=DIw02CaEusY&ab_channel=ProgrammingKnowledge)
        Check from the terminal by the command

        ```bash
            g++ --version
            or
            gcc -v
        ```
Install the latest stable version of [Eigen Library](https://eigen.tuxfamily.org/index.php?title=Main_Page) for performing matrix operations.

## How to Use
- Clone the repository or download the source code files. </br>
- Compile the code using a C++ compiler that supports C++11 or higher and the Eigen library. </br>
- Run the compiled executable.
- The program will generate txt files of signal consisting of a mixture of three sinusoids, add white noise to the signal, apply SVD denoising, and save the denoised signal to a file. </br>
- The original signal, corrupted signal and the denoised signal will also be saved to separate files for comparison. </br>
- Launch [google colab](https://colab.research.google.com/). </br>
- Copy the [python script](https://github.com/Dhruvbhat1729/ICE_Online-Challenge/blob/main/plot.py) and paste it to colab to plot the data obtained in .txt file. </br>
- main.cpp: Contains the main program that generates the signal, adds noise, applies SVD denoising, and saves the denoised signal to a file. </br>
- orignal_signals.txt: Contains the original signal without noise. </br>
- orignal_signals_with_noise.txt: Contains the original signal with added white noise. </br>
- denoised.txt: Contains the denoised signal after applying SVD denoising. </br>

## Dependencies
Eigen C++ library

## License
This project is licensed under the MIT License - see the LICENSE.md file for details.


