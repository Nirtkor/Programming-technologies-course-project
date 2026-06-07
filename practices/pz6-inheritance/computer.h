// Практическое занятие №6. Вариант С. Индивидуальный вариант №1.
// Заголовочный файл: объявления классов с открытым (public) наследованием.
//   Базовый класс      — Computer («Компьютер»);
//   производные классы — Desktop («Настольный компьютер») и Laptop («Ноутбук»).

#ifndef COMPUTER_H
#define COMPUTER_H

// Базовый класс «Компьютер»
class Computer
{
private:
    char model[20];          // модель компьютера
    int  ram;                // объём оперативной памяти, ГБ
public:
    Computer(const char* m, int r);   // конструктор с параметрами
    int         getRam();             // функции доступа
    const char* getModel();
};

// Производный класс «Настольный компьютер» (открытое наследование)
class Desktop : public Computer
{
private:
    int power;               // мощность блока питания, Вт
public:
    Desktop(const char* m, int r, int p);
    int getPower();
};

// Производный класс «Ноутбук» (открытое наследование)
class Laptop : public Computer
{
private:
    int battery;             // время работы от батареи, ч
public:
    Laptop(const char* m, int r, int b);
    int getBattery();
};

#endif
