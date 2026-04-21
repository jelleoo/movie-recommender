#include "RatingManager.h"
#include <iostream>

void RatingManager::addRating(const Rating& rating) {
    ratings.push_back(rating);
}

void RatingManager::printAll() const {
    if (ratings.empty()) {
        std::cout << "등록된 평점이 없습니다." << std::endl;
        return;
    }

    for (const Rating& r : ratings) {
        r.display();
    }
}

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

bool RatingManager::isEmpty() const {
    return ratings.empty();
}