#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>

using namespace std;
#define N 1000000  

int main() {
    vector<double> vec1(N), vec2(N), result(N);
    ifstream fin("vectors.txt");

    // Read data from file
    for (int i = 0; i < N; i++)
        fin >> vec1[i] >> vec2[i];
    fin.close();

    int thread_counts[] = {1, 2, 4, 6, 8, 10, 12, 16, 20, 32, 64}; // Different thread configurations
    int num_configs = sizeof(thread_counts) / sizeof(thread_counts[0]);

    cout << "Threads\tTime (sec)" << endl;

    for (int t = 0; t < num_configs; t++) {
        int num_threads = thread_counts[t];

        double start_time = omp_get_wtime();

        #pragma omp parallel for num_threads(num_threads)
        for (int i = 0; i < N; i++) {
            result[i] = vec1[i] + vec2[i];
        }

        double end_time = omp_get_wtime();
        cout << num_threads << "\t" << (end_time - start_time) << " sec" << endl;
    }

    return 0;
}
