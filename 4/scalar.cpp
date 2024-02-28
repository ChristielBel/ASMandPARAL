#include <iostream>
using namespace std;

int main()
{
    int n = 5;
    int a[5], b[5];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }
    int s = 0;
    n--;
    __asm {
        lea edx, a
        lea ebx, b
        mov eax, [edx]
        mul [ebx]
        mov s, eax
        mov ecx, n
        scalar:
            add ebx, 4
            add edx, 4
            mov eax,[edx]
            mul [ebx]
            add eax, s
            mov s, eax
        loop scalar
        mov s,eax
    }
    cout << s;
}

//x1 y1 z3
//x2 y2 z2
//*=x18x2+y18y2+z1*z2
