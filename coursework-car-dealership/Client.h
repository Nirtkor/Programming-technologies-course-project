#pragma once
#include <string>
#include <iostream>

// Клиент автосалона
class Client {
private:
    int         id;
    std::string fullName;
    std::string phone;
    std::string email;

    static int nextId;

public:
    Client(const std::string& fullName, const std::string& phone,
           const std::string& email = "", int id = -1);

    int         getId()       const { return id; }
    std::string getFullName() const { return fullName; }
    std::string getPhone()    const { return phone; }
    std::string getEmail()    const { return email; }

    friend std::ostream& operator<<(std::ostream& os, const Client& c);

    std::string toFileString() const;
    static void setNextId(int nid) { if (nid >= nextId) nextId = nid + 1; }
};
