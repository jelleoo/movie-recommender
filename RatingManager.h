#pragma once
#include <vector>
#include "Rating.h"

// 평점 데이터를 관리하는 클래스
class RatingManager {
private:
    std::vector<Rating> ratings;   // 평점 목록 저장

public:
    // 평점 추가
    void addRating(const Rating& rating);

    // 전체 평점 출력
    void printAll() const;

    // 특정 영화 ID에 대한 평점만 출력
    void printRatingsByMovieId(int movieId) const;

    // 비어 있는지 확인
    bool isEmpty() const;
};