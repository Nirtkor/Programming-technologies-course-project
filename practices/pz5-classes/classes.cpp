// Практическое занятие №5. Вариант В. Индивидуальный вариант №1.
// Тема: проектирование классов и создание объектов.
//   Задание 1 — класс point (координаты x, y): конструктор с параметрами,
//               функции доступа, деструктор; массив из 4 точек — вершины
//               прямоугольника;
//   Задание 2 — дружественная функция, вычисляющая площадь прямоугольника;
//   Задание 3 — класс «Компьютер» (Приложение, №1); массив из 6 объектов;
//               найти экземпляр с наибольшей оперативной памятью.

#include <iostream>
#include <cstring>
#include <clocale>
using namespace std;

// ===== Задания 1 и 2: класс точки на плоскости =====
class point
{
private:
    int x, y;                      // закрытые члены — координаты точки
public:
    point(int xx, int yy)          // конструктор с параметрами
    {
        x = xx;
        y = yy;
    }
    int getX() { return x; }       // функции доступа к закрытым членам
    int getY() { return y; }
    ~point() {}                    // деструктор (момент уничтожения объекта)

    // дружественная функция вычисления площади прямоугольника
    friend int area(point p[4]);
};

// Дружественная функция: площадь прямоугольника по 4 вершинам.
// Имеет прямой доступ к закрытым членам x, y объектов класса point.
int area(point p[4])
{
    int width  = p[1].x - p[0].x;  // длина горизонтальной стороны
    int height = p[2].y - p[1].y;  // длина вертикальной стороны
    if (width  < 0) width  = -width;
    if (height < 0) height = -height;
    return width * height;
}

// ===== Задание 3: класс по индивидуальному варианту №1 — «Компьютер» =====
class computer
{
private:
    char model[20];                // модель компьютера
    int  ram;                      // объём оперативной памяти, ГБ
public:
    computer(const char* m, int r) // конструктор с параметрами
    {
        strcpy(model, m);
        ram = r;
    }
    int   getRam()   { return ram; }     // функции доступа
    char* getModel() { return model; }
    ~computer() {}                       // деструктор
};

int main()
{
    setlocale(LC_ALL, "Russian");

    // ----- Задание 1: массив из 4 точек — вершины прямоугольника -----
    point rect[4] = { point(0, 0), point(4, 0), point(4, 3), point(0, 3) };

    cout << "Координаты вершин прямоугольника:" << endl;
    for (int i = 0; i < 4; i++)
        cout << "(" << rect[i].getX() << ", " << rect[i].getY() << ")" << endl;

    // ----- Задание 2: площадь через дружественную функцию -----
    cout << "Площадь прямоугольника = " << area(rect) << endl;

    // ----- Задание 3: массив из 6 объектов класса «Компьютер» -----
    computer pc[6] = {
        computer("ASUS",   8),
        computer("Lenovo", 16),
        computer("HP",     4),
        computer("Dell",   32),
        computer("Acer",   16),
        computer("MSI",    8)
    };

    cout << "\nКомпьютеры (модель - ОЗУ):" << endl;
    for (int i = 0; i < 6; i++)
        cout << pc[i].getModel() << " - " << pc[i].getRam() << " ГБ" << endl;

    // Поиск экземпляра с наибольшей оперативной памятью
    int maxIndex = 0;
    for (int i = 1; i < 6; i++)
        if (pc[i].getRam() > pc[maxIndex].getRam())
            maxIndex = i;

    cout << "\nНаибольшая оперативная память у модели "
         << pc[maxIndex].getModel() << " (" << pc[maxIndex].getRam() << " ГБ)" << endl;

    return 0;
}
