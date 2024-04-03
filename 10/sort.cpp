#include <iostream>
#include <thread>
#include <algorithm>

const int ARRAY_SIZE = 10; // Размер массива

// Функция для заполнения массива случайными значениями
void fillArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 100; // Заполняем случайными значениями от 0 до 99
    }
}

// Функция для вывода массива на экран
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// Функция для слияния двух отсортированных половин массива
void merge(int array[], int left, int middle, int right) {
    int size1 = middle - left + 1;
    int size2 = right - middle;

    int* leftArray = new int[size1];
    int* rightArray = new int[size2];

    // Копируем данные во временные массивы
    for (int i = 0; i < size1; ++i)
        leftArray[i] = array[left + i];
    for (int j = 0; j < size2; ++j)
        rightArray[j] = array[middle + 1 + j];

    // Сливаем временные массивы обратно в основной массив
    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2) {
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            ++i;
        }
        else {
            array[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    // Копируем оставшиеся элементы leftArray[], если таковые остались
    while (i < size1) {
        array[k] = leftArray[i];
        ++i;
        ++k;
    }

    // Копируем оставшиеся элементы rightArray[], если таковые остались
    while (j < size2) {
        array[k] = rightArray[j];
        ++j;
        ++k;
    }

    delete[] leftArray;
    delete[] rightArray;
}

// Функция для сортировки массива методом слияния
void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Создаем два потока для сортировки левой и правой половин массива
        std::thread t1(mergeSort, array, left, middle);
        std::thread t2(mergeSort, array, middle + 1, right);

        t1.join();
        t2.join();

        merge(array, left, middle, right);
    }
}

int main() {
    int array[ARRAY_SIZE];

    // Заполняем массив случайными значениями и выводим его на экран
    fillArray(array, ARRAY_SIZE);
    std::cout << "Original array:" << std::endl;
    printArray(array, ARRAY_SIZE);

    // Сортируем массив и выводим его на экран
    mergeSort(array, 0, ARRAY_SIZE - 1);
    std::cout << "Sorted array:" << std::endl;
    printArray(array, ARRAY_SIZE);

    return 0;
}
