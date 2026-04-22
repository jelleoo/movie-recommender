#pragma once
#include <string>
#include <iostream>

// 영화 1개를 표현하는 클래스
class Movie {
private:
    int id;                  // 영화 ID
    std::string title;       // 영화 제목
    std::string genre;       // 영화 장르
    int releaseYear;         // 개봉 연도
    double totalRating;      // 누적 평점 합
    int ratingCount;         // 평점 개수

public:
    // 영화 생성자
    Movie(int id, const std::string& title,
          const std::string& genre, int year);

    // getter: 객체 상태를 바꾸지 않으므로 const
    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getReleaseYear() const;
    double getAverageRating() const;
    int getRatingCount() const;

    // 평점 추가 함수
    // 유효한 평점만 누적해서 평균 계산에 사용
    void addRating(double r);

    // 같은 영화인지 비교
    // 제목 + 개봉연도를 기준으로 비교
    bool operator==(const Movie& o) const;

    // 정렬 기준 정의
    // 평균 평점 오름차순, 같으면 제목 알파벳순
    bool operator<(const Movie& o) const;

    // cout << movie 형태로 출력하기 위한 연산자
    friend std::ostream& operator<<(std::ostream& os, const Movie& m);
};