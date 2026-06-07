#pragma once
#include <string>
#include <iostream>

// Запись о продаже автомобиля
class Sale {
private:
    int         id;
    int         carId;
    int         managerId;
    int         clientId;
    double      basePrice;      // Цена до скидки
    double      finalPrice;     // Итоговая цена
    double      discountPercent;
    std::string date;           // Формат "ДД.ММ.ГГГГ"

    static int nextId;

public:
    Sale(int carId, int managerId, int clientId,
         double basePrice, double discountPercent,
         const std::string& date, int id = -1);

    int         getId()              const { return id; }
    int         getCarId()           const { return carId; }
    int         getManagerId()       const { return managerId; }
    int         getClientId()        const { return clientId; }
    double      getBasePrice()       const { return basePrice; }
    double      getFinalPrice()      const { return finalPrice; }
    double      getDiscountPercent() const { return discountPercent; }
    std::string getDate()            const { return date; }

    // Вычисление цены с учётом скидки
    static double applyDiscount(double price, double discountPct);

    friend std::ostream& operator<<(std::ostream& os, const Sale& s);
    std::string toFileString() const;
    static void setNextId(int nid) { if (nid >= nextId) nextId = nid + 1; }
};
