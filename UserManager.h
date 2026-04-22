#pragma once
#include <vector>
#include <string>
#include "User.h"

// 사용자 데이터를 관리하는 클래스
class UserManager {
private:
    std::vector<User> users;   // 사용자 목록을 private으로 관리

public:
    // 사용자 추가
    void addUser(const User& user);

    // 이름으로 사용자 검색
    User* findByName(const std::string& name);

    // ID로 사용자 검색
    User* findById(const std::string& id);

    // 전체 사용자 출력
    void printAll() const;

    // 비어 있는지 확인
    bool isEmpty() const;
};