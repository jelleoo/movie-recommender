#include "SimilarityCalculator.h"
#include <cmath>

constexpr double NO_COMMON_MOVIE_SCORE = -100.0;

// 두 사용자의 평점 목록을 비교하여 유사도를 계산한다.
// 공식: commonCount * 10 - scoreDiffSum
// 공통 영화가 많을수록 유사도가 올라가고, 같은 영화에 대한 평점 차이가 클수록 유사도가 낮아진다.
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
// 공통 영화가 없으면 비교할 근거가 없으므로 -100 반환
    if (commonCount == 0) {
        return NO_COMMON_MOVIE_SCORE;
    }

    return commonCount * 10 - scoreDiffSum;
}