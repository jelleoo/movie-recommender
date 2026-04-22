#pragma once
#include <string>

// 사용자와 영화 사이의 평점 관계를 표현하는 클래스
class Rating {
private:
    std::string userId;  // 어떤 사용자가
    int movieId;         // 어떤 영화에
    double score;        // 몇 점을 줬는지

public:
    // 평점 생성자
    Rating(const std::string& userId,
           int movieId, double scoreInput);

    // getter
    std::string getUserId() const;
    int getMovieId() const;
    double getScore() const;

    // 평점 정보 출력
    void display() const;
};