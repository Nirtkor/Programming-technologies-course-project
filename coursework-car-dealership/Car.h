#pragma once
#include "Vehicle.h"
#include <sstream>

// Базовый класс автомобиля (наследует Vehicle)
class Car : public Vehicle {
protected:
    int         id;
    std::string color;
    std::string transmission;  // "Механика" или "Автомат"
    std::string fuelType;      // "Бензин", "Дизель", "Электро"
    double      basePrice;
    bool        isSold;

    static int nextId;

public:
    Car(const std::string& brand, const std::string& model,
        int year, double engineVolume, const std::string& color,
        const std::string& transmission, const std::string& fuelType,
        double price, int id = -1);

    virtual ~Car() = default;

    void        display()      const override;
    double      getBasePrice() const override { return basePrice; }
    std::string getType()      const override { return "CAR"; }

    int         getId()           const { return id; }
    bool        getSold()         const { return isSold; }
    std::string getColor()        const { return color; }
    std::string getTransmission() const { return transmission; }
    std::string getFuelType()     const { return fuelType; }
    void        markAsSold()            { isSold = true; }

    bool operator==(const Car& other) const { return id == other.id; }
    friend std::ostream& operator<<(std::ostream& os, const Car& car);

    // Сериализация в строку для сохранения в файл
    virtual std::string toFileString() const;

    static void setNextId(int nid) { if (nid >= nextId) nextId = nid + 1; }
    static int  getNextId()        { return nextId; }
};
