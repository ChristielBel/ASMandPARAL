#include <iostream>
#include <thread>
#include <mutex>

const int ARRAY_SIZE = 10000; 
std::mutex c;

void fillArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = 1;
    }
}

void scalarProduct(int array1[], int array2[], int start, int end, int& result) {
    for (int i = start; i < end; ++i) {
        c.lock();
        result += array1[i] * array2[i];
        c.unlock();
    }
}

int main() {
    int array1[ARRAY_SIZE];
    int array2[ARRAY_SIZE];
    int result = 0;

    fillArray(array1, ARRAY_SIZE);
    fillArray(array2, ARRAY_SIZE);

    std::thread t1(scalarProduct, array1, array2, 0, ARRAY_SIZE / 2, std::ref(result));
    std::thread t2(scalarProduct, array1, array2, ARRAY_SIZE / 2, ARRAY_SIZE, std::ref(result));
    t1.join();
    t2.join();

    std::cout << "Scalar product: " << result << std::endl;

    return 0;
}
