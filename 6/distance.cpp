#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double point1[10], point2[10];
    cout << "Enter the coordinates of point 1 (10 dimensions):" << endl;
    for (int i = 0; i < 10; ++i) {
        cin >> point1[i];
    }

    cout << "Enter the coordinates of point 2 (10 dimensions):" << endl;
    for (int i = 0; i < 10; ++i) {
        cin >> point2[i];
    }

    double distance;
    __asm {
        fldz                  
        mov ecx, 10           

        loop_start:
        fld qword ptr[point1 + ecx * 8 - 8]  
            fsub qword ptr[point2 + ecx * 8 - 8] 
            fmul st(0), st(0)     
            faddp st(1), st(0)    
            loop loop_start       
            fsqrt                 

            fstp qword ptr[distance] 
    }

    cout << "Distance between the two points: " << distance << endl;

    return 0;
}
