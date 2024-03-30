#include <iostream>
#include <time.h>
using namespace std;
int main() {
    srand(time(0));
    setlocale(LC_ALL, "RUS");
    int h;
    int n, m;
    cout << "Введите длину строки: ";
    cin >> n;
    cout << "Введите длину минимальной строки для палиндрома: ";
    cin >> m;
    cout << "Введите количество экспериментов: ";
    cin >> h;
    
    // Задаем начальное значение для генерации
    unsigned int seed = rand();
    unsigned int result=0;
    bool flag=0;
    int i = 0;
    int k = 0;
    __asm {
    loop_i:
        mov esi, seed // Загрузка начального значения в регистр esi
        mov ecx, n // Загрузка количества битов в ecx
        inc seed
        generate_loop :
        mov eax, esi // Помещаем текущее значение seed в eax
            mov edx, 0x41C64E6D // Загружаем множитель
            mul edx // Умножаем текущее значение на множитель
            add eax, 12345 // Добавляем константу
            mov esi, eax // Обновляем seed новым значением

            shr eax, 31 // Сдвигаем значение на 31 бит вправо
            and eax, 1 // Применяем побитовое И к младшему биту

            shl result, 1 // Сдвигаем результат влево на один бит
            or result, eax // Применяем побитовое ИЛИ с текущим битом

            loop generate_loop // Повторяем цикл n раз
          
            mov ecx, m        // Загрузка значения m в регистр ecx
            mov esi, 0        // Загрузка начального индекса в esi
            mov edi, n        // Загрузка длины строки в edi
            sub edi, ecx      // Расчет конечного индекса для сравнения

            outer_loop :
        cmp esi, edi            // Сравнение начального и конечного индексов
            jge done_outer_loop     // Если начальный индекс больше или равен конечному, переходим к завершающей метке

            mov eax, result         // Загружаем число в eax
            mov ebx, eax            // Копируем число в ebx
            mov ecx, esi            // Загружаем значение начального индекса в ecx
            mov edx, ecx            // Копируем значение начального индекса в edx

            inner_loop :
        cmp edx, edi            // Проверяем, достигли ли мы конечного индекса
            jge done_inner_loop     // Если начальный индекс больше или равен конечному, переходим к завершающей метке

            mov eax, result         // Загружаем число в eax
            mov ebx, eax            // Копируем число в ebx
            mov ecx, esi            // Загружаем значение начального индекса в ecx
            mov edx, ecx            // Копируем значение начального индекса в edx

            shr ebx, cl             // Сдвигаем число вправо на начальный индекс
            and ebx, 1              // Проверяем бит по текущему индексу

            mov eax, result         // Загружаем число в eax
            mov edx, eax            // Копируем число в edx
            mov ecx, edi            // Загружаем значение конечного индекса в ecx
            shr edx, cl             // Сдвигаем число вправо на конечный индекс
            and edx, 1              // Проверяем бит по текущему индексу

            cmp ebx, edx            // Сравниваем биты
            jne not_palindrome      // Если они не равны, переходим к метке not_palindrome

            inc esi                 // Увеличиваем начальный индекс
            dec edi                 // Уменьшаем конечный индекс
            jmp inner_loop          // Переходим к следующей итерации внутреннего цикла

            not_palindrome :
        inc esi                 // Увеличиваем начальный индекс
            jmp outer_loop          // Переходим к следующей итерации внешнего цикла

            done_inner_loop :
            inc k           // Устанавливаем флаг в 1, если палиндром найден
            jmp done_outer_loop     // Переходим к завершающей метке внешнего цикла

            done_outer_loop :
            inc i
            mov esi, i
            cmp esi, h
            jl loop_i
    }
    double res = double(k)/double(h);
    // Выводим результат
    std::cout << "Вероятность того, что в строке длины n есть палиндром длины не меньше m: " << res << std::endl;

    return 0;
}
