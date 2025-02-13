#include <iostream>
#include <cstdlib>
#include <omp.h>

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

// Parallel matrix addition using OpenMP
void parallel_matrix_addition(double** A, double** B, double** C, int size, int num_threads) {
    omp_set_num_threads(num_threads);  // Set number of threads
    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)  // Parallelize both loops
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    double end = omp_get_wtime();
    cout << "Parallel Execution Time with " << num_threads << " threads: " << (end - start) << " seconds" << endl;
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

    // Run parallel matrix addition with different thread counts
    int threads[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 32, 64};
    for (int t : threads) {
        parallel_matrix_addition(A, B, C, N, t);
    }

    // Free allocated memory
    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
