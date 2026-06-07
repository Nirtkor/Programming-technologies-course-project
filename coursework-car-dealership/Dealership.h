#pragma once
#include "Car.h"
#include "NewCar.h"
#include "UsedCar.h"
#include "Manager.h"
#include "Client.h"
#include "Sale.h"
#include <vector>
#include <stdexcept>

// Класс автосалона — основная модель (паттерн MVC)
class Dealership {
private:
    std::string          name;
    std::vector<Car*>    inventory;  // Полиморфный список: NewCar и UsedCar
    std::vector<Manager> managers;
    std::vector<Client>  clients;
    std::vector<Sale>    sales;

public:
    explicit Dealership(const std::string& name);
    ~Dealership();  // Освобождает память указателей в inventory

    // ---- Управление инвентарём ----
    void              addCar(Car* car);
    bool              removeCar(int id);
    Car*              findCar(int id)                            const;
    std::vector<Car*> searchByBrand(const std::string& brand)   const;
    std::vector<Car*> getAvailableCars()                        const;

    // ---- Управление менеджерами ----
    void     addManager(const Manager& manager);
    Manager* findManager(int id);

    // ---- Управление клиентами ----
    void    addClient(const Client& client);
    Client* findClient(int id);

    // ---- Оформление сделки ----
    bool processSale(int carId, int managerId, int clientId,
                     double discountPercent, const std::string& date);

    // ---- Статистика ----
    double      getTotalRevenue()      const;
    Manager*    getBestManager();
    std::string getMostPopularBrand()  const;

    // ---- Файловый ввод-вывод ----
    void saveToFile(const std::string& filename)  const;
    bool loadFromFile(const std::string& filename);

    // ---- Доступ к данным (для View) ----
    const std::vector<Car*>&    getInventory() const { return inventory; }
    const std::vector<Manager>& getManagers()  const { return managers; }
    const std::vector<Client>&  getClients()   const { return clients; }
    const std::vector<Sale>&    getSales()     const { return sales; }
    std::string                 getName()      const { return name; }
};
