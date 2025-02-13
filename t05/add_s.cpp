#include <iostream>
#include <cstdlib>
#include <chrono>

using namespace std;

#define N 10000  // Matrix size

// Function to allocate memory for an NxN matrix
double** allocate_matrix(int size) {
    double** matrix = new double*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];
    }
    return matrix;
}

// Function to initialize matrix with random values
void initialize_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = (double)(rand() % 1000) / 100.0;  // Values in range [0,10]
        }
    }
}

// Function to free matrix memory
void free_matrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Serial matrix addition
void serial_matrix_addition(double** A, double** B, double** C, int size) {
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Serial Execution Time: " << duration.count() << " seconds" << endl;
}

// Main function
int main() {
    // Allocate matrices
    double** A = allocate_matrix(N);
    double** B = allocate_matrix(N);
    double** C = allocate_matrix(N);

    // Initialize matrices
    initialize_matrix(A, N);
    initialize_matrix(B, N);

    // Run serial matrix addition
    serial_matrix_addition(A, B, C, N);

    // Free allocated memory
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
