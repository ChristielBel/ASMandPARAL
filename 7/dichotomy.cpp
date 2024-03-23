#include <iostream>
#include <cmath>
# define M_PI           3.14159265358979323846 

int main() {
    setlocale(LC_ALL, "RUS");
    double a = M_PI;
    double b = 1.5 * M_PI;
    double aa = a, bb = b;
    double epsilon = 0.001;
    double resulta, resultb, resultc, c;
    double r = 0;
    double temp=3, temp2=2.0;
    double x=1;
    double diff;
    __asm {
    while_epsilon:
            fld b            
            fsub a          
            fstp diff
            fld epsilon
            fld diff
            fcompp 
            fstsw ax
            sahf
            jb done       

            fld a           
            fld b            
            fadd             
            fld temp2 
            fdiv             
            fstp c
            fld1            
            fld c
            fyl2x            
            fld c
            fsin             
            fld temp
            fmul             
            fadd            
            fstp resultc    

            fld1             
            fld a
            fyl2x            
            fld a
            fsin             
            fld temp
            fmul            
            fadd             
            fstp resulta     
            fld1           

            fld b
            fyl2x           
            fld b
            fsin          
            fld temp
            fmul            
            fadd            
            fstp resultb    

            fld resultc     
            fld resulta      
            fmul             
            fld r           
            fcompp          
            fstsw ax
            sahf
            jb c_a          
            fld c            
            fstp b           
            jmp while_epsilon         

            c_a :
            fld c            
            fstp a           
            jmp while_epsilon         
            done :
    }

    std::cout << "Корень уравнения log2(x) + 3*sin(x) = 0 на отрезке [" << aa << ", " << bb << "] с точностью " << epsilon << " равен:" << c << std::endl;

    return 0;
}
