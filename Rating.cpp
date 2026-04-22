#include "Rating.h"
#include <iostream>

// 생성자
// 점수가 0.0 ~ 5.0 범위를 벗어나면 잘못된 입력값으로 처리(-1.0)
Rating::Rating(const std::string& userId,
               int movieId, double scoreInput)
    : userId(userId), movieId(movieId) {
    if (scoreInput < 0.0 || scoreInput > 5.0) {
        score = -1.0;
    } else {
        score = scoreInput;
    }
}

// getter
std::string Rating::getUserId() const {
    return userId;
}

int Rating::getMovieId() const {
    return movieId;
}

double Rating::getScore() const {
    return score;
}

// 평점 정보 출력
// score가 -1.0이면 잘못된 입력값이라고 표시
void Rating::display() const {
    std::cout << "User ID: " << userId
              << ", Movie ID: " << movieId
              << ", rating: ";

    if (score == -1.0) {
        std::cout << "잘못된 입력값";
    } else {
        std::cout << score;
    }

    std::cout << std::endl;
}