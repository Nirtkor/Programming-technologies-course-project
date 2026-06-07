#include "Dealership.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

Dealership::Dealership(const string& name) : name(name) {}

// Деструктор освобождает динамически выделенные объекты Car
Dealership::~Dealership() {
    for (Car* car : inventory) delete car;
}

void Dealership::addCar(Car* car) {
    inventory.push_back(car);
}

bool Dealership::removeCar(int id) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getId() == id) {
            delete *it;
            inventory.erase(it);
            return true;
        }
    }
    return false;
}

Car* Dealership::findCar(int id) const {
    for (Car* car : inventory) {
        if (car->getId() == id) return car;
    }
    return nullptr;
}

vector<Car*> Dealership::searchByBrand(const string& brand) const {
    vector<Car*> result;
    for (Car* car : inventory) {
        if (car->getBrand() == brand) result.push_back(car);
    }
    return result;
}

// Возвращает только непроданные автомобили
vector<Car*> Dealership::getAvailableCars() const {
    vector<Car*> result;
    for (Car* car : inventory) {
        if (!car->getSold()) result.push_back(car);
    }
    return result;
}

void Dealership::addManager(const Manager& manager) {
    managers.push_back(manager);
}

Manager* Dealership::findManager(int id) {
    for (Manager& m : managers) {
        if (m.getId() == id) return &m;
    }
    return nullptr;
}

void Dealership::addClient(const Client& client) {
    clients.push_back(client);
}

Client* Dealership::findClient(int id) {
    for (Client& c : clients) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

// Оформление продажи: проверяем наличие авто, менеджера и клиента
bool Dealership::processSale(int carId, int managerId, int clientId,
                              double discountPercent, const string& date) {
    Car* car = findCar(carId);
    if (!car || car->getSold()) return false;

    Manager* mgr = findManager(managerId);
    if (!mgr) return false;

    Client* cli = findClient(clientId);
    if (!cli) return false;

    // Создаём запись и помечаем авто как проданный
    sales.emplace_back(carId, managerId, clientId,
                       car->getBasePrice(), discountPercent, date);
    car->markAsSold();
    mgr->incrementSales();
    return true;
}

double Dealership::getTotalRevenue() const {
    double total = 0.0;
    for (const Sale& s : sales) total += s.getFinalPrice();
    return total;
}

// Возвращает менеджера с наибольшим числом продаж
Manager* Dealership::getBestManager() {
    if (managers.empty()) return nullptr;
    return &(*max_element(managers.begin(), managers.end(),
        [](const Manager& a, const Manager& b) {
            return a.getSalesCount() < b.getSalesCount();
        }));
}

// Возвращает марку с наибольшим числом продаж
string Dealership::getMostPopularBrand() const {
    map<string, int> brandCount;
    for (const Sale& s : sales) {
        Car* car = findCar(s.getCarId());
        if (car) ++brandCount[car->getBrand()];
    }
    if (brandCount.empty()) return "Нет данных";
    return max_element(brandCount.begin(), brandCount.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->first;
}

void Dealership::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open())
        throw runtime_error("Не удалось открыть файл: " + filename);

    for (const Car* car : inventory)  file << car->toFileString()  << "\n";
    for (const Manager& m : managers) file << m.toFileString()     << "\n";
    for (const Client& c : clients)   file << c.toFileString()     << "\n";
    for (const Sale& s : sales)       file << s.toFileString()     << "\n";
}

// Вспомогательная функция: читает поле до разделителя '|'
static string nextField(stringstream& ss) {
    string field;
    getline(ss, field, '|');
    return field;
}

bool Dealership::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    // Очищаем старые данные перед загрузкой
    for (Car* car : inventory) delete car;
    inventory.clear();
    managers.clear();
    clients.clear();
    sales.clear();

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string type = nextField(ss);

        if (type == "NEW") {
            int    id      = stoi(nextField(ss));
            string brand   = nextField(ss), model = nextField(ss);
            int    year    = stoi(nextField(ss));
            double eng     = stod(nextField(ss));
            string color   = nextField(ss), trans = nextField(ss), fuel = nextField(ss);
            double price   = stod(nextField(ss));
            bool   sold    = stoi(nextField(ss));
            int    war     = stoi(nextField(ss));
            string config  = nextField(ss);
            auto* car = new NewCar(brand, model, year, eng,
                                   color, trans, fuel, price, war, config, id);
            if (sold) car->markAsSold();
            inventory.push_back(car);

        } else if (type == "USED") {
            int    id      = stoi(nextField(ss));
            string brand   = nextField(ss), model = nextField(ss);
            int    year    = stoi(nextField(ss));
            double eng     = stod(nextField(ss));
            string color   = nextField(ss), trans = nextField(ss), fuel = nextField(ss);
            double price   = stod(nextField(ss));
            bool   sold    = stoi(nextField(ss));
            int    mil     = stoi(nextField(ss));
            string cond    = nextField(ss);
            auto* car = new UsedCar(brand, model, year, eng,
                                    color, trans, fuel, price, mil, cond, id);
            if (sold) car->markAsSold();
            inventory.push_back(car);

        } else if (type == "MANAGER") {
            int    id   = stoi(nextField(ss));
            string name = nextField(ss), dept = nextField(ss);
            double pct  = stod(nextField(ss));
            int    cnt  = stoi(nextField(ss));
            managers.emplace_back(name, dept, pct, id, cnt);

        } else if (type == "CLIENT") {
            int    id    = stoi(nextField(ss));
            string name  = nextField(ss);
            string phone = nextField(ss);
            string email = nextField(ss);
            clients.emplace_back(name, phone, email, id);

        } else if (type == "SALE") {
            int    id   = stoi(nextField(ss));
            int    cId  = stoi(nextField(ss));
            int    mId  = stoi(nextField(ss));
            int    clId = stoi(nextField(ss));
            double bp   = stod(nextField(ss));
            double disc = stod(nextField(ss));
            string date = nextField(ss);
            sales.emplace_back(cId, mId, clId, bp, disc, date, id);
        }
    }
    return true;
}
