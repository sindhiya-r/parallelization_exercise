#include <iostream>
#include <fstream>
#include <iomanip>
#include <random>

#define N 1000000  // At least 1 million numbers

int main() {
    std::ofstream file("large_input.txt");  // Open file for writing
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister RNG
    std::uniform_real_distribution<double> dis(1.0, 100.0); // Uniform distribution

    for (int i = 0; i < N; i++) {
        file << std::fixed << std::setprecision(15) << dis(gen) << "\n";  // Write to file
    }

    file.close();
    std::cout << "File 'large_input.txt' generated with " << N << " double values." << std::endl;

    return 0;
}
