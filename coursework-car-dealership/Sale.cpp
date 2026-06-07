#include "Sale.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int Sale::nextId = 1;

double Sale::applyDiscount(double price, double discountPct) {
    return price * (1.0 - discountPct / 100.0);
}

Sale::Sale(int carId, int managerId, int clientId,
           double basePrice, double discountPercent,
           const string& date, int idVal)
    : carId(carId), managerId(managerId), clientId(clientId),
      basePrice(basePrice), discountPercent(discountPercent), date(date) {
    finalPrice = applyDiscount(basePrice, discountPercent);
    id = (idVal == -1) ? nextId++ : idVal;
    if (idVal != -1 && idVal >= nextId) nextId = idVal + 1;
}

ostream& operator<<(ostream& os, const Sale& s) {
    os << "  ID=" << setw(3) << s.id
       << " | Авто #" << s.carId
       << " | Менеджер #" << s.managerId
       << " | Клиент #" << s.clientId
       << " | Скидка: " << s.discountPercent << "%"
       << " | Итого: " << fixed << setprecision(0) << s.finalPrice << " руб."
       << " | Дата: " << s.date << "\n";
    return os;
}

string Sale::toFileString() const {
    ostringstream oss;
    // Сохраняем basePrice, чтобы при загрузке пересчитать finalPrice
    oss << "SALE|" << id << "|" << carId << "|" << managerId << "|"
        << clientId << "|" << basePrice << "|" << discountPercent << "|" << date;
    return oss.str();
}
