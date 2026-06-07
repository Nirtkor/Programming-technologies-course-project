#pragma once
#include "Dealership.h"
#include <string>

// Класс отображения — вывод информации пользователю (паттерн MVC — View)
class View {
public:
    static void printHeader(const std::string& title);
    static void printSeparator();
    static void printMessage(const std::string& msg);
    static void printError(const std::string& msg);

    static void showMainMenu(const std::string& dealerName);
    static void showCarMenu();
    static void showManagerMenu();
    static void showClientMenu();
    static void showSaleMenu();
    static void showStatsMenu();

    static void showInventory(const std::vector<Car*>& cars, bool availableOnly = false);
    static void showManagers(const std::vector<Manager>& managers);
    static void showClients(const std::vector<Client>& clients);
    static void showSales(const std::vector<Sale>& sales, const Dealership& d);
    static void showStatistics(Dealership& d);

    // Ввод данных от пользователя
    static int    inputInt(const std::string& prompt);
    static double inputDouble(const std::string& prompt);
    static std::string inputString(const std::string& prompt);
};
