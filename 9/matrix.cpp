#include <iostream>
#include <thread>
#include <chrono>

const int MATRIX_SIZE = 100; // Размер квадратных матриц

// Функция для заполнения матриц случайными значениями
void fillMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            matrix[i][j] = rand() % 10; // Заполняем случайными значениями от 0 до 9
        }
    }
}

// Функция для вывода матрицы на экран (для отладки)
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для вычисления элемента результирующей матрицы в указанной части
void multiplyPart(int matrix1[MATRIX_SIZE][MATRIX_SIZE], int matrix2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE], int start, int end) {
    for (int i = start; i < end; ++i) {
        for (int j = 0; j < MATRIX_SIZE; ++j) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; ++k) {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = sum;
        }
    }
}

// Обычная функция для перемножения матриц
void multiplyMatrix(int matrix1[MATRIX_SIZE][MATRIX_SIZE], int matrix2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
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

int main() {
    int matrix1[MATRIX_SIZE][MATRIX_SIZE];
    int matrix2[MATRIX_SIZE][MATRIX_SIZE];
    int result[MATRIX_SIZE][MATRIX_SIZE] = { 0 }; // Инициализируем результирующую матрицу нулями

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
    std::thread t1(multiplyPart, matrix1, matrix2, result, 0, MATRIX_SIZE / 4);
    std::thread t2(multiplyPart, matrix1, matrix2, result, MATRIX_SIZE / 4, MATRIX_SIZE / 2);
    std::thread t3(multiplyPart, matrix1, matrix2, result, MATRIX_SIZE / 2, 3 * MATRIX_SIZE / 4);
    std::thread t4(multiplyPart, matrix1, matrix2, result, 3 * MATRIX_SIZE / 4, MATRIX_SIZE);

    // Ждем завершения всех потоков
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken with threads: " << duration.count() << " microseconds" << std::endl;

    return 0;
}
