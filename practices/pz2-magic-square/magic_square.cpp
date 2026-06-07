// Практическое занятие №2. Вариант В.
// Программа определяет, является ли заданная квадратная матрица
// "магическим" квадратом, то есть равны ли суммы чисел во всех
// строках, всех столбцах и на обеих диагоналях.

#include <iostream>
#include <clocale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");   // вывод русских букв в консоль

    const int N = 3;                // порядок квадратной матрицы

    // Явно заданная квадратная матрица
    int a[N][N] = {
        {2, 7, 6},
        {9, 5, 1},
        {4, 3, 8}
    };

    // Вывод матрицы на экран
    cout << "Матрица:" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }

    // Эталонная сумма — сумма элементов первой строки
    int target = 0;
    for (int j = 0; j < N; j++)
        target = target + a[0][j];

    bool magic = true;              // признак "магического" квадрата

    // Проверка сумм по строкам и столбцам
    for (int i = 0; i < N; i++)
    {
        int rowSum = 0;             // сумма i-й строки
        int colSum = 0;             // сумма i-го столбца
        for (int j = 0; j < N; j++)
        {
            rowSum = rowSum + a[i][j];
            colSum = colSum + a[j][i];
        }
        if (rowSum != target || colSum != target)
            magic = false;
    }

    // Проверка сумм по двум диагоналям
    int diag1 = 0, diag2 = 0;
    for (int i = 0; i < N; i++)
    {
        diag1 = diag1 + a[i][i];            // главная диагональ
        diag2 = diag2 + a[i][N - 1 - i];    // побочная диагональ
    }
    if (diag1 != target || diag2 != target)
        magic = false;

    // Вывод результата
    if (magic)
        cout << "Это магический квадрат. Сумма = " << target << endl;
    else
        cout << "Это НЕ магический квадрат." << endl;

    return 0;
}
