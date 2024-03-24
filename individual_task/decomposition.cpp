#include <iostream>

//разложение вещественного числа в непрерывную дробь
int main() {
    setlocale(LC_ALL, "RUS");
    double x = 3.14159, temp3=1;
    int const n = 6;
    int temp2=1;
    int result[n];
    for (int i = 0; i < n; i++)
        result[i] = 0;
    __asm {
        mov ecx, n 
        lea edi, result 

        start_loop :
        fld x
            fisttp temp2

            mov eax, temp2
            mov[edi], eax

            fld x
            fild temp2
            fsub
            fstp temp3

            fld1
            fld temp3
            fdiv
            fstp x

            add edi, 4

            finit

            loop start_loop
    }
    std::cout << "Непрерывная дробь с точностью до " << n << " членов: [";
    for (int i = 0; i < n - 1; ++i) {
        std::cout << result[i] << ", ";
    }
    std::cout << result[n - 1] << "]" << std::endl;

    return 0;
}
