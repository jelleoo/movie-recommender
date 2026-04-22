#include "User.h"
#include <iostream>

// 생성자: 사용자 기본 정보 초기화
User::User(const std::string& id,
           const std::string& name,
           const std::string& email)
    : id(id), name(name), email(email) {}

// getter
std::string User::getId() const {
    return id;
}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

// 사용자 정보 출력
void User::display() const {
    std::cout << "User ID: " << id
              << ", Name: " << name
              << ", Email: " << email
              << std::endl;
}