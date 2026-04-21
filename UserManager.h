#pragma once
#include <vector>
#include <string>
#include "User.h"

class UserManager {
private:
    std::vector<User> users;

public:
    void addUser(const User& user);
    User* findByName(const std::string& name);
    User* findById(const std::string& id);
    void printAll() const;
    bool isEmpty() const;
};