#include <iostream>
#include <thread>
#include <time.h>
#include <chrono>
using namespace std; 
using namespace std::chrono;

int const n = 1000000;
int a[n];
int summa = 0;

void sum(int start, int end) {
    int localsum = 0;
    for (int i = start; i < end; i++) {
        localsum += a[i];
    }
    summa += localsum;
}

int main()
{
    srand(time(0));
    for (int i = 0; i < n; i++)
        a[i] = rand()%100;
    auto t0 = high_resolution_clock::now();
    thread t1(sum, 0, 25000);
    thread t2(sum, 25000, 5000);
    thread t3(sum, 5000, 75000);
    thread t4(sum, 75000, 100001);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << summa;
    auto t1 = high_resolution_clock::now();
    cout << duration_cast<milliseconds>(t1 - t0).count() << "msec/n";
    return 0;
}
