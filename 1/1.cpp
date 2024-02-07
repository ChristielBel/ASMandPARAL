#include <iostream>
using namespace std;

//арифм прогрессия
int main()
{
    int a1,d,n, sn=0;
    cin >> a1 >> d >> n;
    __asm{
        mov eax, a1
        mov edx, a1
        mov ecx,n

        metka :
            add eax,d
            add edx,eax
        loop metka
        mov sn,edx
    }
    cout << sn;
}
