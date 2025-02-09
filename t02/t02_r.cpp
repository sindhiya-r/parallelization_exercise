#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

#define N 1000000  // At least 1 million numbers

// Function to read data from file
void read_data(std::vector<double> &arr, const std::string &filename, int size) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        file >> arr[i];
    }
    file.close();
}

// Parallel sum using Reduction
double parallel_sum_reduction(std::vector<double> &arr, int size, int threads) {
    double sum = 0.0;
    omp_set_num_threads(threads);
    double start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }

    double end_time = omp_get_wtime();
    std::cout << "Reduction Sum: " << sum << ", Time: " << (end_time - start_time) << " seconds, Threads: " << threads << std::endl;
    return end_time - start_time;
}

int main() {
    std::vector<double> arr(N);
    read_data(arr, "large_input.txt", N);

    int thread_counts[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 32, 64};
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);

    std::ofstream outfile("results_reduction.txt");
    if (!outfile) {
        std::cerr << "Error opening results_reduction.txt for writing!" << std::endl;
        return 1;
    }

    outfile << "Threads Reduction_Time\n";

    for (int i = 0; i < num_tests; i++) {
        int threads = thread_counts[i];
        double time_reduction = parallel_sum_reduction(arr, N, threads);
        outfile << threads << " " << time_reduction << "\n";
    }

    outfile.close();
    return 0;
}
