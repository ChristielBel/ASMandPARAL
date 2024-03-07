#include <iostream>

using namespace std;

int main() {
    const int N = 3; // Размерность матриц
    const int n = N * N;

    int a[n] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // Первая матрица
    int b[n] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 }; // Вторая матрица
    int c[n] = {}; // Результирующая матрица
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
