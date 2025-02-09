#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

#define SIZE 1000000  // 1 Million elements

int main() {
    std::vector<double> A(SIZE), B(SIZE), C(SIZE);
    std::ifstream file("data.txt");

    if (!file) {
        std::cerr << "Error opening file!\n";
        return 1;
    }

    for (size_t i = 0; i < SIZE; i++) {
        file >> A[i] >> B[i];
    }
    file.close();

    int threadCounts[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 32, 64};
    for (int t : threadCounts) {
        omp_set_num_threads(t);
        double start = omp_get_wtime();

        #pragma omp parallel for
        for (size_t i = 0; i < SIZE; i++) {
            C[i] = A[i] + B[i];
        }

        double end = omp_get_wtime();
        double timeTaken = end - start;

        std::cout << "Threads: " << t << ", Time: " << timeTaken << " seconds\n";
        
        // Print first 10 addition results for verification
        std::cout << "First 10 addition results: ";
        for (int i = 0; i < 10; i++) {
            std::cout << C[i] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
