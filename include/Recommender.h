#pragma once
#include <vector>
#include <string>
#include <utility>
#include "Movie.h"
#include "MovieManager.h"
#include "RatingManager.h"

// 추천 알고리즘을 담당하는 클래스이다.
// 추천 기능은 영화 목록(MovieManager)과 평점 데이터(RatingManager)를 함께 사용하므로
// MovieManager에 넣지 않고 별도의 Recommender 클래스로 분리했다.
class Recommender {
private:
    // 원본 Manager 객체를 복사하지 않고 참조로 사용한다.
    // 추천 기능은 영화 목록과 평점 데이터를 읽어야 하므로 참조가 자연스럽다.
    MovieManager& movieMgr;
    RatingManager& ratingMgr;

public:
    Recommender(MovieManager& movieMgr, RatingManager& ratingMgr);

    std::vector<std::pair<std::string, double>> findSimilarUsers(
        const std::string& targetUserId, int k) const;

    std::vector<Movie> recommend(
        const std::string& targetUserId, int k, int n) const;

    std::vector<Movie> recommendByGenre(
        const std::string& targetUserId,
        const std::string& genre,
        int k,
        int n) const;
};