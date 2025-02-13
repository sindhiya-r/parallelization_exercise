#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define N 3000 // Matrix size

// Function to allocate a matrix
double** allocate_matrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
    }
    return matrix;
}

// Function to initialize a matrix with random values
void initialize_matrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

// Serial Matrix Multiplication
void serial_matrix_mult(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; i++) {
        // cout<<i<< " ";
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    double** A = allocate_matrix(N);
    double** B = allocate_matrix(N);
    double** C = allocate_matrix(N);

    initialize_matrix(A, N);
    initialize_matrix(B, N);

    clock_t start = clock();
    serial_matrix_mult(A, B, C, N);
    clock_t end = clock();
    
    printf("Serial Execution Time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Free memory
    for (int i = 0; i < N; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);

    return 0;
}
