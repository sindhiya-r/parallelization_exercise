#include <iostream>
#include <fstream>
#include <random>

#define SIZE 1000000  // 1 Million elements

int main() {
    std::ofstream file("data.txt");
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dis(1.0, 100.0);

    for (size_t i = 0; i < SIZE; i++) {
        file << dis(gen) << " " << dis(gen) << "\n";
    }

    file.close();
    std::cout << "Generated " << SIZE << " pairs of double values in data.txt\n";
    return 0;
}
