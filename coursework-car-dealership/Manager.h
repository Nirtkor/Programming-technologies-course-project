#pragma once
#include <string>
#include <iostream>

// Менеджер автосалона, осуществляющий сделки
class Manager {
private:
    int         id;
    std::string fullName;
    std::string department;
    double      salaryPercent;  // Комиссия от суммы сделки, %
    int         salesCount;

    static int nextId;

public:
    Manager(const std::string& fullName, const std::string& department,
            double salaryPercent, int id = -1, int salesCount = 0);

    int         getId()            const { return id; }
    std::string getFullName()      const { return fullName; }
    std::string getDepartment()    const { return department; }
    double      getSalaryPercent() const { return salaryPercent; }
    int         getSalesCount()    const { return salesCount; }

    void incrementSales() { ++salesCount; }

    bool operator==(const Manager& other) const { return id == other.id; }
    friend std::ostream& operator<<(std::ostream& os, const Manager& m);

    std::string toFileString() const;
    static void setNextId(int nid) { if (nid >= nextId) nextId = nid + 1; }
};
