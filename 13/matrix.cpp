#include <iostream>
#include <thread>
#include <chrono>
#include <ppl.h>

const int MATRIX_SIZE = 1000; // Размер квадратных матриц

// Функция для заполнения матриц случайными значениями
void fillMatrix(int ** matrix) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        matrix[i] = new int[MATRIX_SIZE];
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 10; // Заполняем случайными значениями от 0 до 9
        }
    }
}

// Функция для вывода матрицы на экран (для отладки)
void printMatrix(int** matrix) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Обычная функция для перемножения матриц
void multiplyMatrix(int** matrix1, int** matrix2, int** result) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
}

void paralmult(int** matrix1, int** matrix2, int** result) {
    concurrency::parallel_for(0, MATRIX_SIZE, [=](int i){for (int j = 0; j < MATRIX_SIZE; ++j) {
        int sum = 0;
        for (int k = 0; k < MATRIX_SIZE; ++k) {
            sum += matrix1[i][k] * matrix2[k][j];
        }
        result[i][j] = sum;
    }});
}

int main() {
    int ** matrix1 = new int* [MATRIX_SIZE];
    int**  matrix2 = new int* [MATRIX_SIZE];
    int** result = new int* [MATRIX_SIZE];

    for (int i = 0; i < MATRIX_SIZE; ++i) {
        result[i] = new int[MATRIX_SIZE];
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            result[i][j] =0; // Заполняем случайными значениями от 0 до 9
        }
    }

    // Заполняем матрицы случайными значениями
    fillMatrix(matrix1);
    fillMatrix(matrix2);

    // Измеряем время выполнения умножения матриц без потоков
    auto start = std::chrono::high_resolution_clock::now();
    multiplyMatrix(matrix1, matrix2, result);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << std::endl << "Time taken without threads: " << duration.count() << " microseconds" << std::endl;

    // Создаем и запускаем четыре потока для умножения матрицы
    start = std::chrono::high_resolution_clock::now();
    paralmult(matrix1, matrix2, result);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken with threads: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
