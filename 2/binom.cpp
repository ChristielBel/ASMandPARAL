#include <iostream>
using namespace std;


//n*(n-1)*...*(n-k+1)/k!
int main() {
    int n, k, result=0,a=1,b=1;
    cout << "Enter n and k: ";
    cin >> n >> k;
    int kk = n - k + 1;
    if (n != 1&&k!=1) {
        __asm {
            //вычисление k!
            mov eax, 1
            mov ebx, 1
            mov ecx, k

            metka :
            mul ebx
                inc ebx
                loop metka
                mov a, eax
                //вычисление n*(n-1)*...*(n-k+1)
                mov eax, n         // загружаем n в eax 
                mov ebx, n         // загружаем n в ebx 
                mov ecx, k        // загружаем k в ecx 
                dec ebx            // уменьшаем ebx на 1 (n-1) 
                mov result, eax    // сохраняем значение n в переменной result 

                loop_start :
            mul ebx            // умножаем eax (n) на ebx (n-1) 
                cmp ebx, kk       // сравниваем текущее значение значением n-k+1
                je loop_end        // если равно, завершаем цикл
                dec ebx            // уменьшаем ebx на 1 (n-2, n-3, ...) 
                mov result, eax
                jmp loop_start      // переход к началу цикла

                loop_end :
            mov result, eax
        }
        cout << result << " " << a << endl;

        result = result / a;
    }
    else result = 1;

    cout << "Result: " << result << endl;
    return 0;
}
