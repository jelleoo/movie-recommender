#pragma once
#include <vector>
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

    // 나중에 추천 알고리즘에서 쓸 보조 함수가 있으면 그대로 둬도 됨

    // BaseManager에서 상속받은 순수 가상 함수 구현
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};