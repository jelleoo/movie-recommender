#include "SimilarityCalculator.h"
#include <cmath>   // std::abs

double SimilarityCalculator::calculate(const std::vector<Rating>& user1,
                                       const std::vector<Rating>& user2) {
    int commonCount = 0;        // 공통으로 본 영화 수
    double scoreDiffSum = 0.0;  // 평점 차이의 합

    for (const Rating& r1 : user1) {
        for (const Rating& r2 : user2) {
            if (r1.getMovieId() == r2.getMovieId()) {
                commonCount++;
                scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
            }
        }
    }

    if (commonCount == 0) {
        return -100.0;
    }

    return commonCount * 10 - scoreDiffSum;
}