#include <iostream>
using namespace std;

//разобраться и написать коментарии к программе 
int main()
{
    int n;
    int f2 = 1;
    cin >> n;
    int f1, f3;
    f1 = 1;
    f3 = 0;
    n = n - 2;
    __asm{
        mov EAX, 1; копирует / кладет 1 в eax
        mov EBX, f2; копирует / кладет f2 в ebx
        mov EDX, 0; копирует / кладет 0 edx
        ; счетчик
        mov ECX, n; копирует / кладет n в ecx

        ; add сумма, число.складываает сумму и число, рез - т помещает в сумму
        ; цикл
        metka : 
            add EDX, EAX; к edx прибавляет eax
            add EDX, EBX; к edx прибавляет ebx
            mov EAX, EBX; копирует / кладет ebx в eax
            mov EBX, EDX; копирует / кладет edx в ebx
            mov EDX, 0; копирует / кладет 0 в edx
        loop metka  ;уменьшает счетчик
        mov f1, EBX ; копирует / кладет ebx в f1
    }
    cout << f1;
}
