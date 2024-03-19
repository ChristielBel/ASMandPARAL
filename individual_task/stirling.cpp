#include <iostream>

using namespace std;

int main() {
    setlocale(LC_ALL, "RUS");
    const int n = 40, k=39; 
    const int K = k + 1;

    int s[K];
    for (int i = 0; i < K; i++)
        s[i] = 0;
    // Базовые случаи
    s[0] = 0;
    s[1] = 1;
    int i = 0, j = 0, l=0;
    // Заполнение таблицы с использованием динамического программирования
    __asm {
        mov esi, n
        mov i, 2
        mov edx, k
        loop_i:
        cmp edx, i
        jl min_k
        jge min_i
            loop_j:
            lea eax, s
            mov ecx, i
            dec ecx
            mov ebx, j
            imul ebx, 4
            add eax, ebx
            mov ebx, [eax]
            imul ebx, ecx
            sub eax, 4
            mov ecx, [eax]
            add eax, 4
            sub ecx, ebx
            mov [eax], ecx

            dec j
            cmp j, 0
            jg loop_j

            inc i
            cmp i, esi
            jle loop_i
            jg done
            
            min_k:
            mov j, edx
            cmp edx, i
            jl loop_j
            min_i:
            mov ebx, i
            mov j, ebx
            cmp edx, i
            jge loop_j
            done:
    }



    int result = abs(s[k]);
    cout << "Число Стирлинга первого рода S(" << n << ", " << k << ") = " << result << endl;

    return 0;
}
