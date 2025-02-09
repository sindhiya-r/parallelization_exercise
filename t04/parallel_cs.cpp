#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

#define N 1000000

int main() {
    std::vector<double> A(N), B(N);
    std::ifstream file("input.txt");

    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    for (int i = 0; i < N; i++) {
        file >> A[i];
        B[i] = A[i] * 2;
    }
    file.close();

    int threads[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 32, 64};
    int num_tests = sizeof(threads) / sizeof(threads[0]);

    std::cout << "Threads\tExecution Time (seconds)\n";

    for (int t = 0; t < num_tests; t++) {
        double dot_product = 0.0;
        omp_set_num_threads(threads[t]);

        double start_time = omp_get_wtime();

        #pragma omp parallel
        {
            double local_sum = 0.0;

            #pragma omp for
            for (int i = 0; i < N; i++) {
                local_sum += A[i] * B[i];
            }

            // Critical section to safely update the global sum
            #pragma omp critical
            {
                dot_product += local_sum;
            }
        }

        double end_time = omp_get_wtime();
        double execution_time = end_time - start_time;

        std::cout << threads[t] << "\t" << execution_time << " sec\n";
    }

    return 0;
}
