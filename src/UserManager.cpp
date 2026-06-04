#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
        throw std::runtime_error("사용자 파일을 열 수 없습니다: " + filename);
    }

    std::string line; 
    int lineNum = 0;

    std::getline(file, line); // 헤더 스킵
    lineNum++;

    while (std::getline(file, line)) {
        lineNum++;

        if (line.empty()) {
            continue;
        }

        try {
            std::stringstream ss(line);
            std::string id, name, email;

            std::getline(ss, id, ',');
            std::getline(ss, name, ',');
            std::getline(ss, email, ',');

            if (id.empty() || name.empty()) {
                throw std::invalid_argument("사용자 ID 또는 이름이 비어 있습니다.");
            }

            addUser(User(id, name, email));
        }
        catch (const std::exception& e) {
            std::cerr << filename << " " << lineNum
                      << "번 줄 건너뜀: " << e.what() << std::endl;
        }
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