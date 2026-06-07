#include "NewCar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

NewCar::NewCar(const string& brand, const string& model,
               int year, double engineVolume, const string& color,
               const string& transmission, const string& fuelType,
               double price, int warrantyYears, const string& configuration,
               int idVal)
    : Car(brand, model, year, engineVolume, color, transmission,
          fuelType, price, idVal),
      warrantyYears(warrantyYears), configuration(configuration) {}

void NewCar::display() const {
    cout << "  [НОВЫЙ] ID=" << setw(3) << id
         << " | " << left << setw(10) << brand << setw(12) << model
         << " | " << year << " г."
         << " | " << setw(8) << color
         << " | " << setw(9) << transmission
         << " | " << setw(7) << fuelType
         << " | " << engineVolume << " л"
         << " | Комплект: " << setw(8) << configuration
         << " | Гарантия: " << warrantyYears << " лет"
         << " | " << fixed << setprecision(0) << basePrice << " руб."
         << (isSold ? " [ПРОДАН]" : "") << "\n";
}

string NewCar::toFileString() const {
    ostringstream oss;
    oss << getType() << "|" << id << "|" << brand << "|" << model << "|"
        << year << "|" << engineVolume << "|" << color << "|"
        << transmission << "|" << fuelType << "|" << basePrice << "|"
        << (isSold ? 1 : 0) << "|"
        << warrantyYears << "|" << configuration;
    return oss.str();
}
