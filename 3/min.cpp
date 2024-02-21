#include <iostream>
using namespace std;

//индекс наим эл-та и его значение
int main()
{
    int c = 0, d = 0;
    int a[5];
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }
    __asm {
        lea ebx, a
        mov eax, [ebx]
        mov ecx, 5
        mov edx, 0
        mov c, eax
        mov d, ecx
        _min :
        cmp[ebx], eax
            jge not_min
            mov eax, [ebx]
            mov edx, ecx
            not_min:
            add ebx, 4
        loop _min
        mov ecx, edx
        mov edx, 5
        sub edx, ecx
        mov c, eax
        mov d, edx
    }
    cout << c << " " << d;
}
//LEA записывает адрес элемента
