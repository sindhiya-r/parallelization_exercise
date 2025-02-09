#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 1000000  // At least 1 million numbers

int main() {
    ofstream fout("vectors.txt");
    srand(time(0));

    for (int i = 0; i < N; i++) {
        double num1 = (double)rand() / RAND_MAX * 1000000.0;
        double num2 = (double)rand() / RAND_MAX * 1000000.0;
        fout << num1 << " " << num2 << "\n";
    }

    fout.close();
    cout << "Data file generated with " << N << " pairs of numbers.\n";
    return 0;
}
