#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <thread>
#include <algorithm>
#include "buffered_channel.h"

BufferedChannel<std::pair<int, int>> *cords;

std::vector<int> generateMatrix(int n) {
    std::vector<int> matrix(n * n);
    std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
    for (int i = 0; i < n * n; i++) {
        matrix[i] = (int) (rnd()) % 100;
    }
    return matrix;
}

void multiplyBlocks(const std::vector<int> &A, const std::vector<int> &B, std::vector<int> &C, int n, int blockSize,
                    int upperLeftI, int upperLeftJ) {
    for (int i = upperLeftI; i < std::min(upperLeftI + blockSize, n); i++) {
        for (int j = upperLeftJ; j < std::min(upperLeftJ + blockSize, n); j++) {
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

std::vector<int> multiplyMatrixSequentially(const std::vector<int> &A, const std::vector<int> &B, int blockSize) {
    int matrixSize = (int) std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            multiplyBlocks(A, B, C, matrixSize, blockSize, i, j);
        }
    }
    return C;
}

std::vector<int> multiplyMatrixWithThread(const std::vector<int> &A, const std::vector<int> &B, int blockSize) {
    int matrixSize = (int) std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);
    std::vector<std::thread> threads;
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            threads.emplace_back(multiplyBlocks, std::cref(A), std::cref(B), std::ref(C), matrixSize, blockSize, i, j);
        }
    }
    for (std::thread &thread: threads) {
        thread.join();
    }
    return C;
}


void
multiplyBlocksChannel(const std::vector<int> &A, const std::vector<int> &B, std::vector<int> &C, int n, int blockSize) {
    while (true) {
        auto pair = cords->Recv();
        if (!pair.second) {
            return;
        }
        int I = pair.first.first;
        int J = pair.first.second;
        multiplyBlocks(A, B, C, n, blockSize, I, J);
    }
}

std::vector<int>
multiplyMatrixChannel(const std::vector<int> &A, const std::vector<int> &B, int blockSize, int threadsAmount) {
    int matrixSize = (int) std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);
    std::vector<std::thread> threads;
    if (threadsAmount > 0) {
        cords = new BufferedChannel<std::pair<int, int>>(matrixSize * matrixSize * matrixSize);
        for (int i = 0; i < threadsAmount; i += blockSize) {
            threads.emplace_back(multiplyBlocksChannel, std::cref(A), std::cref(B), std::ref(C), matrixSize, blockSize);
        }
    }

    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            cords->Send(std::pair<int, int>(i, j));
        }
    }
    cords->Close();

    for (auto &thread: threads) {
        thread.join();
    }
    return C;
}

std::vector<long> generateTimeDependence(const std::vector<int> &matrixA, const std::vector<int> &matrixB, int n) {
    std::vector<long> times(2 * n);

    for (int i = 1; i < n; i++) {
        auto start = std::chrono::system_clock::now();
        multiplyMatrixSequentially(matrixA, matrixB, i);
        auto end = std::chrono::system_clock::now();

        auto deltaSequentially = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        multiplyMatrixChannel(matrixA, matrixB, i, 10);
        end = std::chrono::system_clock::now();

        auto deltaWithThread = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        times[i] = deltaSequentially;
        times[n + i] = deltaWithThread;
        std::cout << i + 1 << " " << times[i] << times[i + n] << "\n";
    }
    return times;
}

void run(int n) {
    std::vector<int> A = generateMatrix(n);
    std::vector<int> B = generateMatrix(n);
    std::vector<long> timeDependence = generateTimeDependence(A, B, n);
    double efficient = 0;
    int blockSizeOfMostEffective = 0;
    for (int i = 0; i < n - 1; i++) {
        double temp = 1. * timeDependence[i + 1] / timeDependence[n + i + 1];
        if (temp > efficient) {
            blockSizeOfMostEffective = i + 1;
            efficient = temp;
        }
        std::cout << "Block size: " << i + 1 << " Amount of blocks: " << ceil((n * 1. / (i + 1))) * n
                  << " Delta for sequential: " << timeDependence[i + 1]
                  << " Delta for thread: " << timeDependence[n + i + 1] << " Efficient: "
                  << 1. * timeDependence[i + 1] / timeDependence[n + i + 1] << "\n";
    }
    std::cout << "\nBlock size with most effective multithreading: " << blockSizeOfMostEffective << " Speed up: "
              << efficient;
}

int main() {
    int n = 100;
    std::vector<int> A = generateMatrix(n);
    std::vector<int> B = generateMatrix(n);
    run(n);
}