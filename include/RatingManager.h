#pragma once
#include <vector>
#include <string>
#include "Rating.h"
#include "BaseManager.h"

class RatingManager : public BaseManager {
private:
    std::vector<Rating> ratings;

public:
    void addRating(const Rating& rating);
    void printAll() const;
    void printRatingsByMovieId(int movieId) const;
    bool isEmpty() const;

    // 추천 알고리즘과 유사도 계산에 사용할 보조 함수
    std::vector<Rating> findByUser(const std::string& userId) const;
    std::vector<std::string> getAllUserIds() const;
    const std::vector<Rating>& getRatings() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};