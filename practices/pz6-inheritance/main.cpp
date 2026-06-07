// Практическое занятие №6. Вариант С. Индивидуальный вариант №1.
// Главный файл проекта.
//   Задание 1 — структура классов с открытым наследованием (см. computer.h);
//   Задание 2 — создать по 3 объекта производных классов и определить
//               вычисляемый показатель — экземпляр с наибольшей ОЗУ;
//   Задание 3 — проект размещён в нескольких файлах (computer.h,
//               computer.cpp, main.cpp).

#include <iostream>
#include <clocale>
#include "computer.h"
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    // По 3 объекта каждого производного класса
    Desktop desktops[3] = {
        Desktop("DeskA", 8,  500),
        Desktop("DeskB", 32, 650),
        Desktop("DeskC", 16, 600)
    };
    Laptop laptops[3] = {
        Laptop("LapX", 16, 8),
        Laptop("LapY", 8,  10),
        Laptop("LapZ", 24, 6)
    };

    cout << "Настольные компьютеры (модель, ОЗУ, блок питания):" << endl;
    for (int i = 0; i < 3; i++)
        cout << desktops[i].getModel() << " - " << desktops[i].getRam()
             << " ГБ - " << desktops[i].getPower() << " Вт" << endl;

    cout << "\nНоутбуки (модель, ОЗУ, батарея):" << endl;
    for (int i = 0; i < 3; i++)
        cout << laptops[i].getModel() << " - " << laptops[i].getRam()
             << " ГБ - " << laptops[i].getBattery() << " ч" << endl;

    // Вычисляемый показатель: экземпляр с наибольшей оперативной памятью.
    // Поле ram унаследовано обоими производными классами от базового.
    const char* bestModel = desktops[0].getModel();
    int maxRam = desktops[0].getRam();
    for (int i = 1; i < 3; i++)
        if (desktops[i].getRam() > maxRam)
        {
            maxRam = desktops[i].getRam();
            bestModel = desktops[i].getModel();
        }
    for (int i = 0; i < 3; i++)
        if (laptops[i].getRam() > maxRam)
        {
            maxRam = laptops[i].getRam();
            bestModel = laptops[i].getModel();
        }

    cout << "\nНаибольшая оперативная память: " << bestModel
         << " (" << maxRam << " ГБ)" << endl;

    return 0;
}
