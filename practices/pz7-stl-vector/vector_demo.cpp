// Практическое занятие №7. Вариант С. Индивидуальный вариант №1.
// Тема: STL. Обработка данных в динамических массивах (класс vector).
//   Задание 1 — для структуры классов из ПЗ№6 создать вектор из 4 объектов
//               производного класса и рассчитать вычисляемый показатель
//               (экземпляр с наибольшей оперативной памятью);
//   Задание 2 — очистить вектор и убедиться, что он пуст.

#include <iostream>
#include <vector>
#include <cstring>
#include <clocale>
using namespace std;

// ===== Иерархия классов из Практического занятия №6 =====

// Базовый класс «Компьютер»
class Computer
{
private:
    char model[20];          // модель компьютера
    int  ram;                // объём оперативной памяти, ГБ
public:
    Computer(const char* m, int r) { strcpy(model, m); ram = r; }
    int         getRam()   { return ram; }
    const char* getModel() { return model; }
};

// Производный класс «Ноутбук» (открытое наследование)
class Laptop : public Computer
{
private:
    int battery;             // время работы от батареи, ч
public:
    Laptop(const char* m, int r, int b) : Computer(m, r) { battery = b; }
    int getBattery() { return battery; }
};

int main()
{
    setlocale(LC_ALL, "Russian");

    // ----- Задание 1: вектор из 4 объектов производного класса -----
    vector<Laptop> laptops;       // динамический массив (вектор) нулевой длины

    // Добавление объектов в конец вектора (вектор растёт по мере надобности)
    laptops.push_back(Laptop("LapA", 8,  10));
    laptops.push_back(Laptop("LapB", 32, 6));
    laptops.push_back(Laptop("LapC", 16, 8));
    laptops.push_back(Laptop("LapD", 24, 7));

    cout << "Размер вектора: " << laptops.size() << endl;
    cout << "Содержимое вектора (модель, ОЗУ, батарея):" << endl;
    for (unsigned int i = 0; i < laptops.size(); i++)
        cout << laptops[i].getModel() << " - " << laptops[i].getRam()
             << " ГБ - " << laptops[i].getBattery() << " ч" << endl;

    // Вычисляемый показатель: экземпляр с наибольшей оперативной памятью
    unsigned int maxIndex = 0;
    for (unsigned int i = 1; i < laptops.size(); i++)
        if (laptops[i].getRam() > laptops[maxIndex].getRam())
            maxIndex = i;
    cout << "\nНаибольшая оперативная память: " << laptops[maxIndex].getModel()
         << " (" << laptops[maxIndex].getRam() << " ГБ)" << endl;

    // ----- Задание 2: очистка вектора и проверка -----
    laptops.clear();              // удаление всех элементов вектора
    cout << "\nПосле очистки размер вектора: " << laptops.size() << endl;
    if (laptops.empty())
        cout << "Вектор пуст." << endl;
    else
        cout << "Вектор не пуст." << endl;

    return 0;
}
