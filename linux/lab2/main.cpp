#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

std::vector<int> generateMatrix(int n) {
    std::vector<int> matrix(n * n);
    std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
    for (int i = 0; i < n * n; i++) {
        matrix[i] = (int) rnd() % 2;
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
}

int main() {
    std::vector<int> matrix = generateMatrix(3);
    std::vector<int> mult = multiplyMatrixSequentially(matrix, matrix, 2);
    return 0;
}
