#pragma once
#include <vector>
#include <string>
#include <utility>
#include "Movie.h"
#include "MovieManager.h"
#include "RatingManager.h"

// 추천 알고리즘을 담당하는 클래스
// MovieManager는 영화 정보를 관리하고,
// RatingManager는 평점 데이터를 관리한다.
// 추천 기능은 두 Manager의 데이터를 함께 사용하므로 별도의 Recommender 클래스로 분리함.

class Recommender {
private: // 원본 Manager 객체를 복사하지 않고 참조로 사용.
    MovieManager& movieMgr;
    RatingManager& ratingMgr;

public:
    Recommender(MovieManager& movieMgr, RatingManager& ratingMgr);

    std::vector<std::pair<std::string, double>> findSimilarUsers(
        const std::string& targetUserId, int k) const;

    std::vector<Movie> recommend(
        const std::string& targetUserId, int k, int n) const;
};