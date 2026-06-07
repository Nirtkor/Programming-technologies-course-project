#pragma once
#include <string>
#include <iostream>

// Абстрактный базовый класс для транспортных средств (паттерн MVC — Model)
class Vehicle {
protected:
    std::string brand;
    std::string model;
    int         year;
    double      engineVolume;

public:
    Vehicle(const std::string& brand, const std::string& model,
            int year, double engineVolume)
        : brand(brand), model(model), year(year), engineVolume(engineVolume) {}

    virtual ~Vehicle() = default;

    // Чисто виртуальные функции — обязательны к переопределению в подклассах
    virtual void        display()      const = 0;
    virtual double      getBasePrice() const = 0;
    virtual std::string getType()      const = 0;

    std::string getBrand()        const { return brand; }
    std::string getModel()        const { return model; }
    int         getYear()         const { return year; }
    double      getEngineVolume() const { return engineVolume; }
};
