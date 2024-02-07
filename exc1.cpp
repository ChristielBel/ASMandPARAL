#include <iostream>
using namespace std;
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
        mov EAX, 1
        mov EBX, f2
        mov EDX, 0
        mov ECX, n

        metka : add EDX, EAX
        add EDX, EBX
        mov EAX, EBX
        mov EBX, EDX
        mov EDX, 0
        loop metka
        mov f1, EBX
    }
    cout << f1;
}
