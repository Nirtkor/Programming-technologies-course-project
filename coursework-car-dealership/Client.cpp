#include "Client.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int Client::nextId = 1;

Client::Client(const string& fullName, const string& phone,
               const string& email, int idVal)
    : fullName(fullName), phone(phone), email(email) {
    id = (idVal == -1) ? nextId++ : idVal;
    if (idVal != -1 && idVal >= nextId) nextId = idVal + 1;
}

ostream& operator<<(ostream& os, const Client& c) {
    os << "  ID=" << setw(3) << c.id
       << " | " << left << setw(20) << c.fullName
       << " | Тел: " << setw(14) << c.phone;
    if (!c.email.empty()) os << " | Email: " << c.email;
    os << "\n";
    return os;
}

string Client::toFileString() const {
    ostringstream oss;
    oss << "CLIENT|" << id << "|" << fullName << "|" << phone << "|" << email;
    return oss.str();
}
