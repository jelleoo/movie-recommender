#include "RatingManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

std::vector<Rating> RatingManager::findByUser(const std::string& userId) const {
    std::vector<Rating> result;

    for (const Rating& r : ratings) {
        if (r.getUserId() == userId) {
            result.push_back(r);
        }
    }

    return result;
}

std::vector<std::string> RatingManager::getAllUserIds() const {
    std::vector<std::string> ids;

    for (const Rating& r : ratings) {
        bool exists = false;

        for (const std::string& id : ids) {
            if (id == r.getUserId()) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            ids.push_back(r.getUserId());
        }
    }

    return ids;
}

const std::vector<Rating>& RatingManager::getRatings() const {
    return ratings;
}

void RatingManager::loadFromFile(const std::string& filename) {
    ratings.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("평점 파일을 열 수 없습니다: " + filename);
    }

    std::string line;
    int lineNum = 0;

    std::getline(file, line); // 헤더 스킵
    lineNum++;

    while (std::getline(file, line)) {
        lineNum++;

        if (line.empty()) {
            continue;
        }

        try {
            std::stringstream ss(line);
            std::string userId, token;
            int movieId;
            double score;

            std::getline(ss, userId, ',');

            std::getline(ss, token, ',');
            movieId = std::stoi(token);

            std::getline(ss, token, ',');
            score = std::stod(token);

            if (userId.empty()) {
                throw std::invalid_argument("사용자 ID가 비어 있습니다.");
            }

            if (score < 0.0 || score > 5.0) {
                throw std::out_of_range("평점은 0.0 이상 5.0 이하여야 합니다.");
            }

            addRating(Rating(userId, movieId, score));
        }
        catch (const std::exception& e) {
            std::cerr << filename << " " << lineNum
                      << "번 줄 건너뜀: " << e.what() << std::endl;
        }
    }

    file.close();
}

void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }

    file << "userId,movieId,score" << std::endl;

    for (const Rating& r : ratings) {
        file << r.getUserId() << ","
             << r.getMovieId() << ","
             << r.getScore() << std::endl;
    }

    file.close();
}

int RatingManager::size() const {
    return (int)ratings.size();
}