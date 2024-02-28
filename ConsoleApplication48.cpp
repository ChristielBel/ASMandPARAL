#include <iostream>
using namespace std;

int main()
{
    int n = 3;
    int a[3][3], b[3][3], result[3][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }
    int s1=0, s2=0, s3=0, d=0, k=0;
    n--;
    __asm {
        lea edx, result
        mov ecx, n

        outer:
            lea esi, a
            mov esi, [esi+d*4]
            inc d
            mov eax, [esi]
                inner:
                lea ebx, b
                mov ebx, [ebx+k*4]
                inc k
                mul [ebx]
                mov [edx], eax
                mov edx, [edx+k*4]

                jl outer
        loop outer

    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result[i][j];
        }
        cout << endl;
    }
}

//1 2 1
//4 2 2
//0 1 7
//7 5 1
//2 1 2
//4 3 4
//
//15 10 9 
//40 28 16
//30 22 30
