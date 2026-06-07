#include "Manager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int Manager::nextId = 1;

Manager::Manager(const string& fullName, const string& department,
                 double salaryPercent, int idVal, int salesCount)
    : fullName(fullName), department(department),
      salaryPercent(salaryPercent), salesCount(salesCount) {
    id = (idVal == -1) ? nextId++ : idVal;
    if (idVal != -1 && idVal >= nextId) nextId = idVal + 1;
}

ostream& operator<<(ostream& os, const Manager& m) {
    os << "  ID=" << setw(3) << m.id
       << " | " << left << setw(20) << m.fullName
       << " | Отдел: " << setw(15) << m.department
       << " | Комиссия: " << m.salaryPercent << "%"
       << " | Продаж: " << m.salesCount << "\n";
    return os;
}

string Manager::toFileString() const {
    ostringstream oss;
    oss << "MANAGER|" << id << "|" << fullName << "|"
        << department << "|" << salaryPercent << "|" << salesCount;
    return oss.str();
}
