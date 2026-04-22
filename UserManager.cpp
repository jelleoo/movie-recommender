#include "UserManager.h"
#include <iostream>

// 사용자 추가
void UserManager::addUser(const User& user) {
    users.push_back(user);
}

// 이름으로 사용자 검색
User* UserManager::findByName(const std::string& name) {
    for (User& u : users) {
        if (u.getName() == name) {
            return &u;
        }
    }
    return nullptr;
}

// ID로 사용자 검색
User* UserManager::findById(const std::string& id) {
    for (User& u : users) {
        if (u.getId() == id) {
            return &u;
        }
    }
    return nullptr;
}

// 전체 사용자 출력
void UserManager::printAll() const {
    if (users.empty()) {
        std::cout << "등록된 사용자가 없습니다." << std::endl;
        return;
    }

    for (const User& u : users) {
        u.display();
    }
}

// 비어 있는지 확인
bool UserManager::isEmpty() const {
    return users.empty();
}