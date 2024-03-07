#include <iostream>
using namespace std;

int main()
{
    const int n = 3;
    int a[n], b[n];
    cout << "Vector A:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    cout << "Vector B:" << endl;
    for (int i = 0; i < n; i++){
        cin >> b[i];
    }
    int s = 0;
    __asm {
        lea edx, a
        lea ebx, b
        mov eax, [edx]
        imul [ebx]
        mov s, eax
        mov ecx, n
        cmp ecx, 1
        je _final
        dec ecx
        scalar:
            add ebx, 4
            add edx, 4
            mov eax,[edx]
            imul [ebx]
            add eax, s
            mov s, eax
        loop scalar
        _final:
        mov s, eax
    }
    cout << "Result:" << endl << s;
}
