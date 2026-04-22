#include "RatingManager.h"
#include <iostream>

// 평점 추가
void RatingManager::addRating(const Rating& rating) {
    ratings.push_back(rating);
}

// 전체 평점 출력
void RatingManager::printAll() const {
    if (ratings.empty()) {
        std::cout << "등록된 평점이 없습니다." << std::endl;
        return;
    }

    for (const Rating& r : ratings) {
        r.display();
    }
}

// 특정 영화의 평점만 출력
void RatingManager::printRatingsByMovieId(int movieId) const {
    bool found = false;

    for (const Rating& r : ratings) {
        if (r.getMovieId() == movieId) {
            r.display();
            found = true;
        }
    }

    if (!found) {
        std::cout << "이 영화에 대한 평점이 없습니다." << std::endl;
    }
}

// 비어 있는지 확인
bool RatingManager::isEmpty() const {
    return ratings.empty();
}