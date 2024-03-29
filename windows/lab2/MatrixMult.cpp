﻿#include <iostream>
#include <random>
#include <chrono>
#include <vector>

#define NOMINMAX
#include <windows.h>


std::vector<int> generateMatrix(int n) {
    std::vector<int> matrix(n * n);
    std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
    for (int i = 0; i < n * n; i++) {
        matrix[i] = (int)(rnd()) % 100;
    }
    return matrix;
}

void multiplyBlocks(const std::vector<int>& A, const std::vector<int>& B, std::vector<int>& C, int n, int blockSize,
    int upperLeftI, int upperLeftJ) {
    for (int i = upperLeftI; i < std::min(upperLeftI + blockSize, n); i++) {
        for (int j = upperLeftJ; j < std::min(upperLeftJ + blockSize, n); j++) {
            for (int k = 0; k < n; k++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

std::vector<int> multiplyMatrixSequentially(const std::vector<int>& A, const std::vector<int>& B, int blockSize) {
    int matrixSize = (int)std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            multiplyBlocks(A, B, C, matrixSize, blockSize, i, j);
        }
    }
    return C;
}

struct Params {
    const std::vector<int>& A, B;
    std::vector<int>& C;
    int n;
    int blockSize;
    int upperLeftI;
    int upperLeftJ;

    Params(const std::vector<int>& A,const std::vector<int> B, std::vector<int> C, int n, int blockSize, int upperLeftI, int upperLeftJ) : A(A), B(B), C(C) {
        this->n = n;
        this->blockSize = blockSize;
        this->upperLeftI = upperLeftI;
        this->upperLeftJ = upperLeftJ;
    }
};

std::vector<int> multiplyMatrixWithThread(const std::vector<int>& A, const std::vector<int>& B, int blockSize) {
    int matrixSize = (int)std::sqrt(A.size());
    std::vector<int> C(matrixSize * matrixSize, 0);

    std::vector<HANDLE> threads;
    
    for (int i = 0; i < matrixSize; i += blockSize) {
        for (int j = 0; j < matrixSize; j += blockSize) {
            Params params(A, B, C, matrixSize, blockSize, i, j);
            threads.emplace_back(CreateThread(nullptr, 0,
                reinterpret_cast<LPTHREAD_START_ROUTINE>(&multiplyBlocks), &params, 0, nullptr));
        }
    }
    auto* thrArr = new HANDLE[threads.size()];
    for (int i = 0; i < threads.size(); ++i) {
        thrArr[i] = threads[i];
    }

    WaitForMultipleObjects((DWORD)blockSize, thrArr, TRUE, INFINITE);
    return C;
}

std::vector<long> generateTimeDependence(const std::vector<int>& matrixA, const std::vector<int>& matrixB, int n) {
    std::vector<long> times(2 * n);

    for (int i = 1; i < n; i++) {
        auto start = std::chrono::system_clock::now();
        multiplyMatrixSequentially(matrixA, matrixB, i);
        auto end = std::chrono::system_clock::now();

        auto deltaSequentially = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = std::chrono::system_clock::now();
        multiplyMatrixWithThread(matrixA, matrixB, i);
        end = std::chrono::system_clock::now();

        auto deltaWithThread = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        times[i] = deltaSequentially;
        times[n + i] = deltaWithThread;
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
            << 1. * timeDependence[i + 1] / timeDependence[n + i + 1] << std::endl;
    }
    std::cout << "\nBlock size with most effective multithreading: " << blockSizeOfMostEffective << " Speed up: " << efficient;
}

int main() {
    int n = 100;
    run(n);
}