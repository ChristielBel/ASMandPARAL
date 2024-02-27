#include <iostream>
using namespace std;

int main() {
    int a[5];
    cout << "Enter 5 numbers: ";
    for (int i = 0; i < 5; i++) {
        cin >> a[i];
    }

    __asm {
        mov ecx, 5          
        lea ebx, a          
        outer_loop :
        mov edx, 0      
            mov eax, ecx    
            dec eax         
            inner_loop :
               mov esi, [ebx + eax * 4]    
                cmp esi, [ebx + eax * 4 - 4]
                jge not_swap                
                xchg esi, [ebx + eax * 4 - 4]
                mov[ebx + eax * 4], esi    
                inc edx                     
                not_swap :
                dec eax                     
                jnz inner_loop              
            mov eax, ecx                    
            dec eax                         
            test edx, edx                  
            jnz outer_loop                  
    }

    cout << "Sorted array: ";
    for (int i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}
