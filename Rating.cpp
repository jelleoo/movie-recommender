#include "Rating.h"
#include <iostream>

Rating::Rating()
    : userId(""), movieId(0), score(0.0) {}

Rating::Rating(const std::string& userId,
               int movieId, double scoreInput)
    : userId(userId), movieId(movieId) {
    if (scoreInput < 0.0 || scoreInput > 5.0) {
        score = 0.0;
    } else {
        score = scoreInput;
    }
}

std::string Rating::getUserId() const {
    return userId;
}

int Rating::getMovieId() const {
    return movieId;
}

double Rating::getScore() const {
    return score;
}

void Rating::display() const {
    std::cout << "User ID: " << userId
              << ", Movie ID: " << movieId
              << ", Score: " << score
              << std::endl;
}