// Практическое занятие №6. Вариант С. Индивидуальный вариант №1.
// Файл реализации методов классов.

#include <cstring>
#include "computer.h"

// ===== Базовый класс «Компьютер» =====
Computer::Computer(const char* m, int r)
{
    strcpy(model, m);
    ram = r;
}
int         Computer::getRam()   { return ram; }
const char* Computer::getModel() { return model; }

// ===== Производный класс «Настольный компьютер» =====
// Аргументы конструктора производного класса частично передаются базовому
// (через расширенную форму объявления : Computer(m, r)).
Desktop::Desktop(const char* m, int r, int p) : Computer(m, r)
{
    power = p;
}
int Desktop::getPower() { return power; }

// ===== Производный класс «Ноутбук» =====
Laptop::Laptop(const char* m, int r, int b) : Computer(m, r)
{
    battery = b;
}
int Laptop::getBattery() { return battery; }
