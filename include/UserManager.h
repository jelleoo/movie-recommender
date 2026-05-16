#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "BaseManager.h"

class UserManager : public BaseManager {
private:
    std::vector<User> users;

public:
    void addUser(const User& user);
    User* findByName(const std::string& name);
    User* findById(const std::string& id);
    void printAll() const;
    bool isEmpty() const;

    // BaseManager에서 상속받은 순수 가상 함수 구현
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};