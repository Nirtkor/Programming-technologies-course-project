#include "Car.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int Car::nextId = 1;

Car::Car(const string& brand, const string& model,
         int year, double engineVolume, const string& color,
         const string& transmission, const string& fuelType,
         double price, int idVal)
    : Vehicle(brand, model, year, engineVolume),
      color(color), transmission(transmission),
      fuelType(fuelType), basePrice(price), isSold(false) {
    // Если id не передан — присваиваем автоматически
    id = (idVal == -1) ? nextId++ : idVal;
    if (idVal != -1 && idVal >= nextId) nextId = idVal + 1;
}

void Car::display() const {
    cout << "  ID=" << setw(3) << id
         << " | " << left << setw(10) << brand << setw(12) << model
         << " | " << year << " г."
         << " | " << setw(8) << color
         << " | " << setw(9) << transmission
         << " | " << setw(7) << fuelType
         << " | " << engineVolume << " л"
         << " | " << fixed << setprecision(0) << basePrice << " руб."
         << (isSold ? " [ПРОДАН]" : "") << "\n";
}

ostream& operator<<(ostream& os, const Car& car) {
    car.display();
    return os;
}

string Car::toFileString() const {
    ostringstream oss;
    oss << getType() << "|" << id << "|" << brand << "|" << model << "|"
        << year << "|" << engineVolume << "|" << color << "|"
        << transmission << "|" << fuelType << "|" << basePrice << "|"
        << (isSold ? 1 : 0);
    return oss.str();
}
