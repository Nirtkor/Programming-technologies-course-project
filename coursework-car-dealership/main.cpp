/*
 * Курсовой проект по дисциплине "Технологии программирования"
 * Тема 31: "Продажа автомобилей"
 *
 * Реализация системы управления автосалоном с применением
 * объектно-ориентированного программирования на языке C++.
 * Архитектура: паттерн Model-View-Controller (MVC).
 *
 * Иерархия классов:
 *   Vehicle (абстрактный)
 *     └── Car
 *           ├── NewCar   (новый автомобиль)
 *           └── UsedCar  (подержанный автомобиль)
 *   Manager  — менеджер, осуществляющий сделки
 *   Client   — покупатель автомобиля
 *   Sale     — запись о совершённой сделке
 *   Dealership (модель) — управляет всеми объектами
 *   View     — вывод и ввод данных
 */

#include "Dealership.h"
#include "View.h"
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

// Возвращает текущую дату в формате ДД.ММ.ГГГГ
static string currentDate() {
    time_t t = time(nullptr);
    tm*    lt = localtime(&t);
    char   buf[11];
    strftime(buf, sizeof(buf), "%d.%m.%Y", lt);
    return buf;
}

// Заполнение демонстрационными данными при первом запуске
static void loadDemoData(Dealership& d) {
    // Новые автомобили
    d.addCar(new NewCar("Toyota",   "Camry",    2024, 2.5, "Белый",
                         "Автомат", "Бензин", 3200000, 3, "Комфорт"));
    d.addCar(new NewCar("Hyundai",  "Solaris",  2024, 1.6, "Серый",
                         "Автомат", "Бензин", 1850000, 3, "Базовая"));
    d.addCar(new NewCar("Kia",      "K5",       2023, 2.0, "Чёрный",
                         "Автомат", "Бензин", 2750000, 2, "Люкс"));
    d.addCar(new NewCar("BMW",      "X5",       2024, 3.0, "Синий",
                         "Автомат", "Бензин", 8900000, 3, "Комфорт"));

    // Подержанные автомобили
    d.addCar(new UsedCar("Toyota", "Corolla", 2019, 1.6, "Красный",
                          "Механика", "Бензин", 1100000, 65000, "Хорошее"));
    d.addCar(new UsedCar("Nissan", "X-Trail", 2020, 2.0, "Белый",
                          "Автомат",  "Бензин", 1800000, 42000, "Отличное"));
    d.addCar(new UsedCar("Ford",   "Focus",   2018, 1.5, "Синий",
                          "Механика", "Бензин",  850000, 98000, "Среднее"));

    // Менеджеры
    d.addManager(Manager("Иванов Алексей Петрович",   "Новые авто",      3.0));
    d.addManager(Manager("Смирнова Ольга Ивановна",   "Новые авто",      3.0));
    d.addManager(Manager("Петров Дмитрий Сергеевич",  "Подержанные авто",2.5));

    // Клиенты
    d.addClient(Client("Козлов Андрей Владимирович",  "+7-921-111-22-33", "kozlov@mail.ru"));
    d.addClient(Client("Морозова Екатерина Николаевна","+7-921-444-55-66"));
    d.addClient(Client("Волков Игорь Александрович",   "+7-921-777-88-99"));
}

// Подменю: управление автомобилями
static void menuCars(Dealership& d) {
    int choice;
    do {
        View::showCarMenu();
        choice = View::inputInt("Выберите: ");
        switch (choice) {
            case 1:
                View::printHeader("Все автомобили");
                View::showInventory(d.getInventory());
                break;
            case 2:
                View::printHeader("Доступные автомобили");
                View::showInventory(d.getInventory(), true);
                break;
            case 3: {
                // Ввод нового автомобиля
                View::printHeader("Добавить новый автомобиль");
                string brand  = View::inputString("Марка: ");
                string model  = View::inputString("Модель: ");
                int    year   = View::inputInt   ("Год выпуска: ");
                double eng    = View::inputDouble ("Объём двигателя (л): ");
                string color  = View::inputString("Цвет: ");
                string trans  = View::inputString("КПП (Механика/Автомат): ");
                string fuel   = View::inputString("Топливо (Бензин/Дизель/Электро): ");
                double price  = View::inputDouble ("Цена (руб.): ");
                int    war    = View::inputInt   ("Гарантия (лет): ");
                string conf   = View::inputString("Комплектация: ");
                d.addCar(new NewCar(brand, model, year, eng,
                                    color, trans, fuel, price, war, conf));
                View::printMessage("Автомобиль добавлен.");
                break;
            }
            case 4: {
                // Ввод подержанного автомобиля
                View::printHeader("Добавить подержанный автомобиль");
                string brand  = View::inputString("Марка: ");
                string model  = View::inputString("Модель: ");
                int    year   = View::inputInt   ("Год выпуска: ");
                double eng    = View::inputDouble ("Объём двигателя (л): ");
                string color  = View::inputString("Цвет: ");
                string trans  = View::inputString("КПП (Механика/Автомат): ");
                string fuel   = View::inputString("Топливо: ");
                double price  = View::inputDouble ("Начальная цена (руб.): ");
                int    mil    = View::inputInt   ("Пробег (км): ");
                string cond   = View::inputString("Состояние (Отличное/Хорошее/Среднее): ");
                d.addCar(new UsedCar(brand, model, year, eng,
                                     color, trans, fuel, price, mil, cond));
                View::printMessage("Автомобиль добавлен.");
                break;
            }
            case 5: {
                View::showInventory(d.getInventory());
                int id = View::inputInt("ID автомобиля для удаления: ");
                if (d.removeCar(id)) View::printMessage("Удалён.");
                else View::printError("Автомобиль с таким ID не найден.");
                break;
            }
            case 6: {
                string brand = View::inputString("Введите марку: ");
                auto result  = d.searchByBrand(brand);
                View::printHeader("Результаты поиска: " + brand);
                View::showInventory(result);
                break;
            }
            case 0: break;
            default: View::printError("Неверный выбор.");
        }
    } while (choice != 0);
}

// Подменю: управление менеджерами
static void menuManagers(Dealership& d) {
    int choice;
    do {
        View::showManagerMenu();
        choice = View::inputInt("Выберите: ");
        switch (choice) {
            case 1:
                View::printHeader("Список менеджеров");
                View::showManagers(d.getManagers());
                break;
            case 2: {
                View::printHeader("Добавить менеджера");
                string name = View::inputString("ФИО: ");
                string dept = View::inputString("Отдел: ");
                double pct  = View::inputDouble ("Комиссия (%): ");
                d.addManager(Manager(name, dept, pct));
                View::printMessage("Менеджер добавлен.");
                break;
            }
            case 0: break;
            default: View::printError("Неверный выбор.");
        }
    } while (choice != 0);
}

// Подменю: управление клиентами
static void menuClients(Dealership& d) {
    int choice;
    do {
        View::showClientMenu();
        choice = View::inputInt("Выберите: ");
        switch (choice) {
            case 1:
                View::printHeader("Список клиентов");
                View::showClients(d.getClients());
                break;
            case 2: {
                View::printHeader("Добавить клиента");
                string name  = View::inputString("ФИО: ");
                string phone = View::inputString("Телефон: ");
                string email = View::inputString("Email (Enter — пропустить): ");
                d.addClient(Client(name, phone, email));
                View::printMessage("Клиент добавлен.");
                break;
            }
            case 0: break;
            default: View::printError("Неверный выбор.");
        }
    } while (choice != 0);
}

// Оформление продажи
static void menuSale(Dealership& d) {
    View::showSaleMenu();

    View::printHeader("Доступные автомобили");
    View::showInventory(d.getInventory(), true);

    View::printHeader("Менеджеры");
    View::showManagers(d.getManagers());

    View::printHeader("Клиенты");
    View::showClients(d.getClients());

    View::printSeparator();
    int    carId   = View::inputInt   ("ID автомобиля: ");
    int    mgrId   = View::inputInt   ("ID менеджера: ");
    int    cliId   = View::inputInt   ("ID клиента: ");
    double disc    = View::inputDouble("Скидка (%): ");
    string date    = currentDate();

    if (d.processSale(carId, mgrId, cliId, disc, date)) {
        View::printMessage("Продажа оформлена! Дата: " + date);
    } else {
        View::printError("Не удалось оформить сделку. "
                         "Проверьте ID или наличие автомобиля.");
    }
}

int main() {
    Dealership dealership("АвтоПрайм");
    loadDemoData(dealership);

    const string dataFile = "dealership.dat";
    int choice;

    do {
        View::showMainMenu(dealership.getName());
        choice = View::inputInt("Выберите: ");
        switch (choice) {
            case 1: menuCars(dealership);     break;
            case 2: menuManagers(dealership); break;
            case 3: menuClients(dealership);  break;
            case 4: menuSale(dealership);     break;
            case 5:
                View::showStatistics(dealership);
                View::printHeader("История продаж");
                View::showSales(dealership.getSales(), dealership);
                break;
            case 6:
                try {
                    dealership.saveToFile(dataFile);
                    View::printMessage("Данные сохранены в " + dataFile);
                } catch (const exception& e) {
                    View::printError(e.what());
                }
                break;
            case 7:
                if (dealership.loadFromFile(dataFile))
                    View::printMessage("Данные загружены из " + dataFile);
                else
                    View::printError("Файл не найден: " + dataFile);
                break;
            case 0:
                std::cout << "\n  До свидания!\n\n";
                break;
            default:
                View::printError("Неверный выбор.");
        }
    } while (choice != 0);

    return 0;
}
