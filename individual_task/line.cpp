#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

int** picture;
const int h = 21; // Высота изображения
const int w = 34; // Ширина изображения
//построение фона
void create(int h, int w)
{
    picture = new int* [h];
    for (int i = 0; i < h; i++)
    {
        picture[i] = new int[w];
        for (int j = 0; j < w; j++)
            picture[i][j] = 0;
    }
}

//вывод
void output(int h, int w)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            cout << picture[i][j] << " ";
        cout << endl;
    }
}

void letter(int a, int b, int c, int d, int width, int image_height) {
    int horizontal_segments = width / 2; // Вычисляем количество горизонтальных сегментов

    // Ограничиваем диапазон генерации начальной координаты a, чтобы отрезок генерировался только в верхней половине изображения
    a = max(a, 0);
    a = min(a, image_height / 2 - 1);

    // Заполняем всю область отрезка
    for (int i = a; i <= c; i++) {
        for (int j = b; j <= d; j++) {
            picture[i][j] = 1;
        }
    }
}

bool check(int a, int b, int c, int d)
{
    return !(b < c || d < a);
}

// Функция для преобразования двумерного массива в одномерный массив строк
void convertToRows(int* result) {
    // Проходим по каждой строке двумерного массива
    for (int i = 0; i < h; ++i) {
        // Преобразуем строку из двоичного представления в десятичное число
        int decimalValue = 0;
        for (int j = w - 1; j >= 0; --j) {
            decimalValue += picture[i][j] * pow(2, w - 1 - j);
        }
        result[i] = decimalValue;
    }
}

// поиск отрезков
int find(int h, int w) {
    int count = 0; // переменная для подсчета отрезков
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (picture[i][j] == 1) {
                int a = i, b = j;
                while (picture[a][b] != 0 && a < h) {
                    picture[a][b] = 0;
                    b++;
                }
                int y2 = b - 1; // Конечная координата y (правый конец отрезка)
                a = i; // Возвращаемся на исходную строку
                b = j; // Возвращаемся на начало отрезка
                while (picture[a][b] != 0 && b < y2) {
                    picture[a][b] = 0;
                    a++;
                }
                count++; // увеличиваем счетчик найденных отрезков
            }
        }
    }
    return count; // возвращаем количество найденных отрезков
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "RUS");
    create(h, w);
    vector<pair<int, int>> vc;
    int k = 7;
    for (int i = 0; i < k; i++)
    {
        while (true)
        {
            int width = 4 + rand() % 9; // Случайная ширина отрезка
            int x1 = rand() % (h / 2); // Случайная начальная координата x в верхней половине
            int y1 = rand() % (w - width); // Случайная начальная координата y
            int x2 = x1; // Начальная координата x и конечная координата x совпадают для горизонтального отрезка
            int y2 = y1 + width - 1;

            bool flag = 1;
            if (vc.size() > 0)
                for (int j = 0; j < vc.size() - 1; j += 2)
                    if (check(x1, x2, vc[j].first, vc[j + 1].first) && check(y1, y2, vc[j].second, vc[j + 1].second)) flag = 0;

            if (flag)
            {
                letter(x1, y1, x2, y2, w, h);
                x1--;
                x2++;
                y1--;
                y2++;
                vc.push_back(make_pair(x1, y1));
                vc.push_back(make_pair(x2, y2));
                break;
            }
        }
    }


    // Вывод изображения с отрезками
    output(h, w);
    cout << endl;
    int result[h];
    convertToRows(result);
    for (int i = 0; i < h; ++i) {
        std::cout << result[i] << endl;
    }
    int i = 0, j = 0, count=0;
    __asm {
        mov esi, h
        mov i, 0
        loop_i:
            lea ecx, result
            mov edx, i
            imul edx, 4
            add ecx, edx
            mov edx, [ecx]
            test edx, edx; Проверяем, не равен ли регистр нулю
            jz next_loop
            bsr ecx, edx
          
                
                find_loop1:
           cmp ecx, -1
            jle next_loop
            dec ecx
            bt edx, ecx
            jc find_loop1
                inc count
               find_loop : 
           cmp ecx, -1
               jle next_loop
            dec ecx
            bt edx, ecx
            jnc find_loop

            jc find_loop1

            next_loop:
            inc i
            cmp i, esi
            jl loop_i
    }
    cout << count;
    //// Поиск и вывод количества отрезков на картинке
    //int segments_count = find(h, w);
    //cout << "Количество отрезков: " << segments_count << endl;
    //output(h, w);
    return 0;
}
