#include <iostream>

using namespace std;
int main()
{
    int x, m, k;
    cin >> x >> m;
    __asm {
        mov eax, x
        mov ebx, m
        cmp ebx, 1
        je final_loop
        jl loop_0
        bsr ecx, ebx
        dec ecx
        _loop :
        imul eax
            bt ebx, ecx
            jnc loop_u
            imul eax, x

        loop_u :
            dec ecx
            cmp ecx, -1
            jne _loop

        loop_0:
        cmp eax, x
        jg final_loop
        mov eax, 1
        final_loop:
        mov k, eax
    }
    cout << k;
}

//бинарный алгоритм возвдеения большого числа в степень 
//если 0 - текущий результат возводится в квадрат
//если 1 - текущий резльтат возводится в квадрат и умножается на х
