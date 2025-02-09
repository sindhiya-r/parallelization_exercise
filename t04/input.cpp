#include <iostream>
#include <fstream>
#include <cstdlib>

#define N 1000000  // 1 Million

int main() {
    std::ofstream file("input.txt");
    srand(42);  // Seed for reproducibility
    for (int i = 0; i < N; i++) {
        file << (double)(rand() % 1000) / 100.0 << " ";  // Random double values
    }
    file.close();
    std::cout << "File input.txt generated with " << N << " double values.\n";
    return 0;
}
