#include "UsedCar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

UsedCar::UsedCar(const string& brand, const string& model,
                 int year, double engineVolume, const string& color,
                 const string& transmission, const string& fuelType,
                 double price, int mileage, const string& condition,
                 int idVal)
    : Car(brand, model, year, engineVolume, color, transmission,
          fuelType, price, idVal),
      mileage(mileage), condition(condition) {}

// Расчёт цены с учётом пробега
double UsedCar::getBasePrice() const {
    double discount = (mileage / 10000) * 0.005;
    if (discount > 0.30) discount = 0.30;
    return basePrice * (1.0 - discount);
}

void UsedCar::display() const {
    cout << "  [Б/У]   ID=" << setw(3) << id
         << " | " << left << setw(10) << brand << setw(12) << model
         << " | " << year << " г."
         << " | " << setw(8) << color
         << " | " << setw(9) << transmission
         << " | " << setw(7) << fuelType
         << " | " << engineVolume << " л"
         << " | Пробег: " << setw(7) << mileage << " км"
         << " | " << setw(10) << condition
         << " | " << fixed << setprecision(0) << getBasePrice() << " руб."
         << (isSold ? " [ПРОДАН]" : "") << "\n";
}

string UsedCar::toFileString() const {
    ostringstream oss;
    oss << getType() << "|" << id << "|" << brand << "|" << model << "|"
        << year << "|" << engineVolume << "|" << color << "|"
        << transmission << "|" << fuelType << "|" << basePrice << "|"
        << (isSold ? 1 : 0) << "|"
        << mileage << "|" << condition;
    return oss.str();
}
