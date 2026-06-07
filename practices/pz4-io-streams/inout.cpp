// Практическое занятие №4. Вариант В. Индивидуальный вариант №1.
// Тема: разработка программ ввода-вывода данных.
//   Задание 1 — с помощью манипуляторов в цикле сформировать матрицу
//               (Приложение А, №1) и вывести её на экран;
//   Задание 2 — преобразовать строку «Zero One Null» (Приложение Б, №1):
//               заменить все буквы 'e' на 'o', используя только
//               библиотечные функции (без обращения по индексу),
//               и записать результат в файл three.txt;
//   Задание 3 — по выбору пользователя выводить на экран матрицу,
//               исходную или преобразованную строку.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <clocale>
using namespace std;

const int N = 6;   // размер матрицы

// Формирование матрицы: во втором столбце — буквы A..F, остальное — '*'
void formMatrix(char m[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (j == 1)
                m[i][j] = 'A' + i;   // второй столбец заполняется буквами
            else
                m[i][j] = '*';
}

// Вывод матрицы на экран с помощью манипулятора setw (форматирование)
void printMatrix(char m[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << setw(3) << m[i][j];
        cout << endl;
    }
}

// Преобразование строки: заменить все 'e' на 'o'.
// Используется только библиотечная функция strchr, без индексации.
void transform(char* s)
{
    char* p = strchr(s, 'e');     // поиск первого символа 'e'
    while (p != NULL)
    {
        *p = 'o';                 // замена символа через указатель
        p = strchr(p + 1, 'e');   // поиск следующего 'e'
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // ----- Задание 1: формирование и вывод матрицы -----
    char matrix[N][N];
    formMatrix(matrix);

    // ----- Задание 2: преобразование строки и запись в файл -----
    char source[50] = "Zero One Null";   // исходная строка (Приложение Б, №1)
    char result[50];
    strcpy(result, source);              // копия для преобразования
    transform(result);                   // "Zero One Null" -> "Zoro Ono Null"

    ofstream fout;
    fout.open("three.txt");              // создание потока и открытие файла
    if (!fout)                           // проверка открытия файла
        cout << "Ошибка открытия файла!" << endl;
    else
    {
        fout << result << endl;          // запись преобразованной строки
        fout.close();                    // закрытие файла
    }

    // ----- Задание 3: меню пользователя -----
    int choice;
    do
    {
        cout << "\nМеню:" << endl;
        cout << "1 - показать матрицу" << endl;
        cout << "2 - показать исходную строку" << endl;
        cout << "3 - показать преобразованную строку" << endl;
        cout << "0 - выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
            case 1: printMatrix(matrix);          break;
            case 2: cout << source << endl;       break;
            case 3: cout << result << endl;       break;
            case 0: cout << "Выход из программы." << endl; break;
            default: cout << "Неверный пункт меню!" << endl;
        }
    }
    while (choice != 0);

    return 0;
}
