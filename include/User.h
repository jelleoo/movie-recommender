#pragma once
#include <string>

// 사용자 1명을 표현하는 클래스
class User {
private:
    std::string id;      // 사용자 ID
    std::string name;    // 사용자 이름
    std::string email;   // 사용자 이메일

public:
    // 사용자 생성자
    User(const std::string& id,
         const std::string& name,
         const std::string& email);

    // getter: 객체 상태를 바꾸지 않으므로 const
    std::string getId() const;
    std::string getName() const;
    std::string getEmail() const;

    // 사용자 정보 출력
    void display() const;
};