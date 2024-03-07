#include <iostream>

using namespace std;

int main() {
    const int N = 1; // Размерность матриц
    const int n = N * N;

    int a[n]; // Первая матрица
    int b[n]; // Вторая матрица
    int c[n] = {}; // Результирующая матрица
    cout << "Matrix A:" << endl;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Matrix B:" << endl;
    for (int i = 0; i < n; i++)
        cin >> b[i];
    int i = 0, j = 0, k = 0, s=0;
    __asm {
        mov esi, N
        mov i, 0
        loop_i:
            mov j, 0
            loop_j:
                mov k, 0
                mov s, 0
                loop_k:
                lea eax, a
                mov edx, i
                imul edx, 4
                imul edx, N
                add eax, edx
                mov edx, k
                imul edx, 4
                add eax, edx

                lea ebx, b
                mov edx, j
                imul edx, 4
                add ebx, edx
                mov edx, k
                imul edx, 4
                imul edx, N
                add ebx, edx

                mov eax, [eax]
                mov ebx, [ebx]
                imul ebx
                add s, eax
                inc k
                cmp k, esi
                jl loop_k

                lea ecx, c
                mov edx, j
                imul edx, 4
                add ecx, edx
                mov edx, i
                imul edx, 4
                imul edx, N
                add ecx, edx
                mov edx, s
                mov [ecx], edx

                inc j
                cmp j, esi
                jl loop_j

                inc i
                cmp i, esi
                jl loop_i
    }

    int counter = 0;

    // Вывод результата
    cout << "Resultant Matrix: " << endl;
    for (int i = 0; i < n; i++) {
        counter++;
        cout << c[i] << " ";
        if (counter == N) { cout << endl; counter = 0; }
    }

    return 0;
}
