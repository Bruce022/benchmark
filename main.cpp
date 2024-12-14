#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <cstdlib>
#include <ctime>

// Benchmark class to measure time
class Benchmark {
public:
    Benchmark() { start = std::chrono::high_resolution_clock::now(); }

    long long elapsed() const {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start;
};

// Generate a random vector of integers
std::vector<int> generateRandomVector(size_t n) {
    std::vector<int> vec(n);
    for (size_t i = 0; i < n; ++i) {
        vec[i] = rand() % 1000; // Smaller range for easier testing
    }
    return vec;
}

// Classic Bubble Sort
void bubbleSort(std::vector<int>& vec, std::function<bool(int, int)> comp) {
    size_t n = vec.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (comp(vec[j + 1], vec[j])) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator

    size_t dataSize = 5000; // Use a manageable size for testing
    auto data = generateRandomVector(dataSize);

    auto comparator = [](int a, int b) { return a < b; };

    Benchmark timer;
    bubbleSort(data, comparator);
    std::cout << "Bubble Sort completed for " << dataSize << " elements in "
              << timer.elapsed() << " µs\n";

    return 0;
}
