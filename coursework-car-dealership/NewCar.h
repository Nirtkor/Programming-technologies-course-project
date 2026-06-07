#pragma once
#include "Car.h"

// Новый автомобиль: добавляет гарантию и комплектацию
class NewCar : public Car {
private:
    int         warrantyYears;
    std::string configuration;  // "Базовая", "Комфорт", "Люкс"

public:
    NewCar(const std::string& brand, const std::string& model,
           int year, double engineVolume, const std::string& color,
           const std::string& transmission, const std::string& fuelType,
           double price, int warrantyYears, const std::string& configuration,
           int id = -1);

    void        display()      const override;
    std::string getType()      const override { return "NEW"; }
    std::string toFileString() const override;

    int         getWarrantyYears() const { return warrantyYears; }
    std::string getConfiguration() const { return configuration; }
};
