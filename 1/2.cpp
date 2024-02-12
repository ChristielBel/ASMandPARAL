#include <iostream>
using namespace std;

//факториал
int main()
{
    int n, sn = 0;
    cin >> n;
    __asm {
        mov eax, 1
        mov ebx, 1
        mov ecx, n

        metka :
        mul ebx
        inc ebx
        loop metka
        mov sn, eax
    }
    cout << sn;
}
