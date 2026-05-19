#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <algorithm>
#include <set>
#include <map>
// 추천 알고리즘을 담당하는 클래스
// MovieManager는 영화 정보를 관리하고,
// RatingManager는 평점 데이터를 관리한다.
// 추천 기능은 두 Manager의 데이터를 함께 사용하므로 별도의 Recommender 클래스로 분리함.

Recommender::Recommender(MovieManager& movieMgr, RatingManager& ratingMgr) // movieMgr와 ratingMgr는 참조 멤버이므로 생성자 초기화 리스트에서 초기화
    : movieMgr(movieMgr), ratingMgr(ratingMgr) {}
// 추천 대상 사용자와 다른 모든 사용자의 유사도를 계산한다.
// 유사도 점수가 높은 순서대로 정렬한 뒤 상위 k명 반환.
std::vector<std::pair<std::string, double>> Recommender::findSimilarUsers(
    const std::string& targetUserId, int k) const {

    std::vector<std::pair<std::string, double>> similarities;
    std::vector<Rating> myRatings = ratingMgr.findByUser(targetUserId);

    if (myRatings.empty()) {
        return similarities;  // 추천 대상 사용자의 평점이 없으면 비교할 데이터가 없으므로 빈 결과 반환
    }

    for (const std::string& otherId : ratingMgr.getAllUserIds()) {
        if (otherId == targetUserId) continue;  // 자기 자신과는 유사도를 계산하지 않는다.

        std::vector<Rating> otherRatings = ratingMgr.findByUser(otherId);
        double sim = SimilarityCalculator::calculate(myRatings, otherRatings); // 두 사용자의 평점 목록을 비교하여 유사도 점수를 계산한다.

        if (sim > 0) {    // 유사도가 양수인 사용자만 추천에 사용한다, 공통 영화가 없으면 SimilarityCalculator에서 -100을 반환하므로 제외
            similarities.push_back({otherId, sim});
        }
    }

    std::sort(similarities.begin(), similarities.end(),
        [](const std::pair<std::string, double>& a,
           const std::pair<std::string, double>& b) {      // pair의 두번째값은 유사도 점수, 유사도가 큰 사용자가 앞에 오도록 람다로 내림차순 정렬
            return a.second > b.second;
        });

    if ((int)similarities.size() > k) {  // 유사 사용자가 k명보다 많으면 상위 k명만 남긴다, k명보다 적으면 있는 만큼만 사용
        similarities.resize(k);
    }

    return similarities;
}

// recommend 알고리즘의 전체 흐름
// 1. 추천 대상 사용자의 평점 목록을 가져온다.
// 2. 유사도 상위 k명의 사용자를 찾는다.
// 3. 내가 이미 본 영화는 추천 후보에서 제외한다.
// 4. 유사 사용자가 4.0 이상으로 평가한 영화를 후보로 모은다.
// 5. 가중 평균으로 추천 점수를 계산하고 내림차순 정렬 후 n개 반환한다.
std::vector<Movie> Recommender::recommend(
    const std::string& targetUserId, int k, int n) const {

    std::vector<Movie> result;
    std::vector<Rating> myRatings = ratingMgr.findByUser(targetUserId);

    if (myRatings.empty()) {        // 평점이 하나도 없는 사용자는 취향 비교가 불가능하므로 추천하지 않는다.
        return result;
    }
        
    std::vector<std::pair<std::string, double>> similarUsers =
        findSimilarUsers(targetUserId, k);

    if (similarUsers.empty()) {     // 유사 사용자가 없으면 추천 후보를 만들 수 없으므로 빈 결과 반환
        return result;
    }
    
    std::set<int> watchedMovieIds;  // set으로 내가 이미 본 영화 ID를 저장.

    for (const Rating& r : myRatings) {
        watchedMovieIds.insert(r.getMovieId());
    }
    // 영화별 추천 점수를 누적하기 위한 map
    // weightedSum: 유사도 * 평점의 합
    // weightSum: 유사도 합
    // 최종 추천 점수 = weightedSum / weightSum    
    std::map<int, double> weightedSum;
    std::map<int, double> weightSum;

    for (const std::pair<std::string, double>& userSim : similarUsers) {
        std::string otherId = userSim.first;
        double sim = userSim.second;

        std::vector<Rating> otherRatings = ratingMgr.findByUser(otherId);

        for (const Rating& r : otherRatings) {
            int movieId = r.getMovieId();
            double score = r.getScore();
            // 유사 사용자가 높게 평가한 영화만 추천 후보로 사용.
            // 평점 4.0 이상을 "좋아한 영화"의 기준으로 함. 
            if (score >= 4.0 && watchedMovieIds.find(movieId) == watchedMovieIds.end()) {
                weightedSum[movieId] += sim * score;
                weightSum[movieId] += sim;
            }
        }
    }

    std::vector<std::pair<int, double>> scoredMovies;

    for (const std::pair<const int, double>& item : weightedSum) {
        int movieId = item.first;

        if (weightSum[movieId] > 0) {
            double finalScore = weightedSum[movieId] / weightSum[movieId];  // 가중 평균 계산
            scoredMovies.push_back({movieId, finalScore});
        }
    }
    
    // 추천 점수가 높은 영화가 먼저 오도록 내림차순 정렬.
    // 점수가 같으면 movieId가 작은 순서로 정렬.

    std::sort(scoredMovies.begin(), scoredMovies.end(),     
        [](const std::pair<int, double>& a,                 
           const std::pair<int, double>& b) {
            if (a.second != b.second) {                     
                return a.second > b.second;
            }
            return a.first < b.first;
        });

    int limit = n;      // 추천 후보가 n개보다 적으면 있는 만큼만 반환

    if ((int)scoredMovies.size() < limit) {
        limit = (int)scoredMovies.size();
    }

    for (int i = 0; i < limit; i++) {
        Movie* foundMovie = movieMgr.findById(scoredMovies[i].first);

        if (foundMovie != nullptr) {
            result.push_back(*foundMovie);
        }
    }

    return result;
}