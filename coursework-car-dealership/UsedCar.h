#pragma once
#include "Car.h"

// Подержанный автомобиль: добавляет пробег и состояние
class UsedCar : public Car {
private:
    int         mileage;    // Пробег, км
    std::string condition;  // "Отличное", "Хорошее", "Среднее"

public:
    UsedCar(const std::string& brand, const std::string& model,
            int year, double engineVolume, const std::string& color,
            const std::string& transmission, const std::string& fuelType,
            double price, int mileage, const std::string& condition,
            int id = -1);

    void        display()      const override;
    std::string getType()      const override { return "USED"; }
    // Цена б/у авто снижается на 0.5% за каждые 10 000 км (макс. 30%)
    double      getBasePrice() const override;
    std::string toFileString() const override;

    int         getMileage()   const { return mileage; }
    std::string getCondition() const { return condition; }
};
