#include <iostream>
#include <thread>
#include <chrono>

const int ARRAY_SIZE = 1000000; // Размер массива

// Функция для заполнения массива случайными значениями
void fillArray(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 100; // Заполняем случайными значениями от 0 до 99
    }
}

// Обычная функция для вычисления суммы элементов массива
int sumArray(int* array, int size) {
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    return sum;
}

// Функция для вычисления суммы части массива в указанном диапазоне
void sumPart(int* array, int start, int end, int& result) {
    for (int i = start; i < end; ++i) {
        result += array[i];
    }
}

int main() {
    int* array = new int[ARRAY_SIZE]; // Выделение памяти для массива в динамической памяти

    // Заполняем массив случайными значениями
    fillArray(array, ARRAY_SIZE);

    // Измеряем время выполнения без использования потоков
    auto start = std::chrono::high_resolution_clock::now();
    int totalSum = sumArray(array, ARRAY_SIZE);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken without threads: " << duration.count() << " microseconds" << std::endl;

    // Измеряем время выполнения с использованием четырех потоков
    start = std::chrono::high_resolution_clock::now();
    int totalSumThreads = 0;
    std::thread t1(sumPart, array, 0, ARRAY_SIZE / 4, std::ref(totalSumThreads));
    std::thread t2(sumPart, array, ARRAY_SIZE / 4, ARRAY_SIZE / 2, std::ref(totalSumThreads));
    std::thread t3(sumPart, array, ARRAY_SIZE / 2, 3 * ARRAY_SIZE / 4, std::ref(totalSumThreads));
    std::thread t4(sumPart, array, 3 * ARRAY_SIZE / 4, ARRAY_SIZE, std::ref(totalSumThreads));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken with threads: " << duration.count() << " microseconds" << std::endl;

    // Освобождаем память, выделенную для массива
    delete[] array;

    return 0;
}
