#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000  // Number of elements in the array

int main() {
    double *numbers = (double*) malloc(N * sizeof(double));
    FILE *file = fopen("large_input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Reading numbers from file
    for (int i = 0; i < N; i++) {
        fscanf(file, "%lf", &numbers[i]);
    }
    fclose(file);

    // Explicit list of thread counts to iterate over
    int thread_counts[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 32, 64};

    // Loop over the defined thread counts
    for (int i = 0; i < sizeof(thread_counts)/sizeof(thread_counts[0]); i++) {
        int threads = thread_counts[i];
        double sum = 0.0;
        double start_time = omp_get_wtime();  // Start time measurement

        // Set the number of threads
        omp_set_num_threads(threads);

        // Parallel Sum using Critical Section
        #pragma omp parallel
        {
            double local_sum = 0.0;
            #pragma omp for
            for (int i = 0; i < N; i++) {
                local_sum += numbers[i];
            }

            // Critical section to add local sum to the global sum
            #pragma omp critical
            {
                sum += local_sum;
            }
        }

        double end_time = omp_get_wtime();  // End time measurement
        double time_taken = end_time - start_time;

        // Printing the result in the desired format
        printf("Critical Sum: %.5e, Time: %.7f seconds, Threads: %d\n", sum, time_taken, threads);
    }

    free(numbers);
    return 0;
}
