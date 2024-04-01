#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "RUS");
    const int n = 2;
    const int k = 4;
    int f[k] = { 0,1,0,1};
    int g[k] = { 1,0,0, 1};
    int s[k];
    for (int i = 0; i < k; i++) {
       s[i] = i;
    }
    int fg[n] = { 0 };
    int superposition[k] = { 0 };
    int check[n] = { 0 };
    int i = 0, j = 0, l=0, p=0, o=0;
    __asm {
       mov j, 0
       loop_j:
       mov esi, n
           mov eax, 0
           loop_i:
       dec esi
           cmp esi, 1
           jl change_g
           lea ebx, s
           lea ecx, fg
           mov edx, j
           imul edx, 4
           add ebx, edx
           mov edx, eax
           imul edx, 4
           add ecx, edx
           inc eax
           mov edx, [ebx]
           bt edx, esi
           jnc zero
           jmp one

               zero:
            mov [ecx], 0
            jmp loop_i

               one:
            mov [ecx], 1
            jmp loop_i

                change_g :
            lea ebx, g
                lea ecx, fg
                mov edx, j
                imul edx, 4
                add ebx, edx
                mov edx, n
                dec edx
                imul edx, 4
                add ecx, edx
                mov ebx, [ebx]
                mov[ecx], ebx

                mov l, 0
                mov esi, n
                dec esi
                mov o, 0

                super:
                mov p, 0
                lea eax, s
                mov ecx, l
                imul ecx, 4
                add eax, ecx
                mov eax, [eax]
                bt eax, esi
                jnc check_zero
                jmp check_one

                    superr :
                    inc l
                    mov esi, n
                    dec esi
                    mov o, 0
                    jmp super

                check_zero:
                lea ebx, check
                mov ecx,o
                    inc o
                imul ecx, 4
                add ebx, ecx
                mov [ebx],0
                dec esi
                cmp esi, 0
                jl next_loop
                    jmp super

                check_one:
                lea ebx, check
                    mov ecx, o
                    inc o
                    imul ecx, 4
                    add ebx, ecx
                    mov[ebx], 1
                dec esi
                    cmp esi, 0
                    jl next_loop
                    jmp super

                    next_loop:
                mov ecx, n
                cmp ecx, p
                je fill_loop
                lea eax, check
                    lea ebx, fg
                    mov ecx, p
                    imul ecx, 4
                    add eax, ecx
                    add ebx, ecx
                    mov esi, [eax]
                    mov edi, [ebx]
                    cmp edi, esi
                    jne superr
                    inc p
                    jmp next_loop

                    fill_loop:
                    lea eax, superposition
                    lea ebx, f
                    mov ecx, l
                    imul ecx, 4
                    add ebx, ecx
                        mov ecx, j
                        imul ecx, 4
                        add eax, ecx
                        mov ecx, [ebx]
                        mov [eax], ecx

          inc j
          mov esi, k
          cmp esi, j
          jg loop_j
    }
    for (int i = 0; i < k; i++)
        cout << superposition[i] << " ";
    return 0;
}
