#pragma once
#include <string>

// 세 Manager가 공통으로 가져야 하는 인터페이스를 강제하는 부모 클래스
class BaseManager {
public:
    // CSV 파일 로드
    virtual void loadFromFile(const std::string& filename) = 0;

    // CSV 파일 저장
    virtual void saveToFile(const std::string& filename) const = 0;

    // 현재 저장된 데이터 개수 반환
    virtual int size() const = 0;

    // 상속 구조에서는 virtual 소멸자 필요
    virtual ~BaseManager() {}
};