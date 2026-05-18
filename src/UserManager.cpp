#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

void UserManager::addUser(const User& user) {
    users.push_back(user);
}

User* UserManager::findByName(const std::string& name) {
    for (User& u : users) {
        if (u.getName() == name) {
            return &u;
        }
    }
    return nullptr;
}

User* UserManager::findById(const std::string& id) {
    for (User& u : users) {
        if (u.getId() == id) {
            return &u;
        }
    }
    return nullptr;
}

void UserManager::printAll() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return;
    }

    for (const User& u : users) {
        u.display();
    }
}

bool UserManager::isEmpty() const {
    return users.empty();
}

void UserManager::loadFromFile(const std::string& filename) {
    users.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 열 수 없습니다." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, name, email;

        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, email, ',');

        addUser(User(id, name, email));
    }

    file.close();
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }

    file << "id,name,email" << std::endl;

    for (const User& u : users) {
        file << u.getId() << ","
             << u.getName() << ","
             << u.getEmail() << std::endl;
    }

    file.close();
}

int UserManager::size() const {
    return (int)users.size();
}