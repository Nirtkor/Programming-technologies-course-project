#include "View.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void View::printHeader(const string& title) {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║  " << left << setw(36) << title << "║\n";
    cout << "╚══════════════════════════════════════╝\n";
}

void View::printSeparator() {
    cout << "──────────────────────────────────────\n";
}

void View::printMessage(const string& msg) {
    cout << "  [OK] " << msg << "\n";
}

void View::printError(const string& msg) {
    cout << "  [ОШИБКА] " << msg << "\n";
}

void View::showMainMenu(const string& dealerName) {
    printHeader("Автосалон: " + dealerName);
    cout << "  1. Управление автомобилями\n"
         << "  2. Управление менеджерами\n"
         << "  3. Управление клиентами\n"
         << "  4. Оформить продажу\n"
         << "  5. Статистика\n"
         << "  6. Сохранить данные\n"
         << "  7. Загрузить данные\n"
         << "  0. Выход\n";
    printSeparator();
}

void View::showCarMenu() {
    printHeader("Управление автомобилями");
    cout << "  1. Показать все автомобили\n"
         << "  2. Показать доступные (не проданные)\n"
         << "  3. Добавить новый автомобиль\n"
         << "  4. Добавить подержанный автомобиль\n"
         << "  5. Удалить автомобиль\n"
         << "  6. Поиск по марке\n"
         << "  0. Назад\n";
    printSeparator();
}

void View::showManagerMenu() {
    printHeader("Управление менеджерами");
    cout << "  1. Показать всех менеджеров\n"
         << "  2. Добавить менеджера\n"
         << "  0. Назад\n";
    printSeparator();
}

void View::showClientMenu() {
    printHeader("Управление клиентами");
    cout << "  1. Показать всех клиентов\n"
         << "  2. Добавить клиента\n"
         << "  0. Назад\n";
    printSeparator();
}

void View::showSaleMenu() {
    printHeader("Оформление продажи");
}

void View::showStatsMenu() {
    printHeader("Статистика");
}

void View::showInventory(const vector<Car*>& cars, bool availableOnly) {
    if (cars.empty()) {
        cout << "  Список пуст.\n";
        return;
    }
    int count = 0;
    for (const Car* car : cars) {
        // Фильтруем по доступности, если запрошено
        if (availableOnly && car->getSold()) continue;
        car->display();
        ++count;
    }
    if (count == 0) cout << "  Нет доступных автомобилей.\n";
    else cout << "  Всего: " << count << " авт.\n";
}

void View::showManagers(const vector<Manager>& managers) {
    if (managers.empty()) { cout << "  Список менеджеров пуст.\n"; return; }
    for (const Manager& m : managers) cout << m;
    cout << "  Всего: " << managers.size() << " менеджеров.\n";
}

void View::showClients(const vector<Client>& clients) {
    if (clients.empty()) { cout << "  Список клиентов пуст.\n"; return; }
    for (const Client& c : clients) cout << c;
    cout << "  Всего: " << clients.size() << " клиентов.\n";
}

void View::showSales(const vector<Sale>& sales, const Dealership& d) {
    if (sales.empty()) { cout << "  История продаж пуста.\n"; return; }
    for (const Sale& s : sales) {
        // Выводим имена вместо id для читаемости
        Car*     car = d.findCar(s.getCarId());
        Manager* mgr = const_cast<Dealership&>(d).findManager(s.getManagerId());
        Client*  cli = const_cast<Dealership&>(d).findClient(s.getClientId());
        cout << "  ID=" << setw(3) << s.getId()
             << " | " << (car ? car->getBrand() + " " + car->getModel() : "?")
             << " | Мен.: " << (mgr ? mgr->getFullName() : "?")
             << " | Клиент: " << (cli ? cli->getFullName() : "?")
             << " | Скидка: " << s.getDiscountPercent() << "%"
             << " | " << fixed << setprecision(0) << s.getFinalPrice() << " руб."
             << " | " << s.getDate() << "\n";
    }
    cout << "  Всего сделок: " << sales.size() << "\n";
}

void View::showStatistics(Dealership& d) {
    printHeader("Статистика автосалона");
    cout << fixed << setprecision(0);
    cout << "  Общая выручка:      " << d.getTotalRevenue() << " руб.\n";
    cout << "  Всего продаж:       " << d.getSales().size() << "\n";
    cout << "  Авто в наличии:     " << d.getAvailableCars().size() << "\n";

    Manager* best = d.getBestManager();
    if (best)
        cout << "  Лучший менеджер:    " << best->getFullName()
             << " (" << best->getSalesCount() << " продаж)\n";

    cout << "  Популярная марка:   " << d.getMostPopularBrand() << "\n";
}

int View::inputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) { cin.ignore(); return value; }
        // Очищаем поток при некорректном вводе
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Введите целое число.\n";
    }
}

double View::inputDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) { cin.ignore(); return value; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Введите число.\n";
    }
}

string View::inputString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}
