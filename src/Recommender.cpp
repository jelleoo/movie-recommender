#include "Recommender.h"
#include "SimilarityCalculator.h"
#include <algorithm>
#include <set>
#include <map>

Recommender::Recommender(MovieManager& movieMgr, RatingManager& ratingMgr)
    : movieMgr(movieMgr), ratingMgr(ratingMgr) {}

std::vector<std::pair<std::string, double>> Recommender::findSimilarUsers(
    const std::string& targetUserId, int k) const {

    std::vector<std::pair<std::string, double>> similarities;
    std::vector<Rating> myRatings = ratingMgr.findByUser(targetUserId);

    if (myRatings.empty()) {
        return similarities;
    }

    for (const std::string& otherId : ratingMgr.getAllUserIds()) {
        if (otherId == targetUserId) continue;

        std::vector<Rating> otherRatings = ratingMgr.findByUser(otherId);
        double sim = SimilarityCalculator::calculate(myRatings, otherRatings);

        if (sim > 0) {
            similarities.push_back({otherId, sim});
        }
    }

    std::sort(similarities.begin(), similarities.end(),
        [](const std::pair<std::string, double>& a,
           const std::pair<std::string, double>& b) {
            return a.second > b.second;
        });

    if ((int)similarities.size() > k) {
        similarities.resize(k);
    }

    return similarities;
}

std::vector<Movie> Recommender::recommend(
    const std::string& targetUserId, int k, int n) const {

    std::vector<Movie> result;
    std::vector<Rating> myRatings = ratingMgr.findByUser(targetUserId);

    if (myRatings.empty()) {
        return result;
    }

    std::vector<std::pair<std::string, double>> similarUsers =
        findSimilarUsers(targetUserId, k);

    if (similarUsers.empty()) {
        return result;
    }

    std::set<int> watchedMovieIds;

    for (const Rating& r : myRatings) {
        watchedMovieIds.insert(r.getMovieId());
    }

    std::map<int, double> weightedSum;
    std::map<int, double> weightSum;

    for (const std::pair<std::string, double>& userSim : similarUsers) {
        std::string otherId = userSim.first;
        double sim = userSim.second;

        std::vector<Rating> otherRatings = ratingMgr.findByUser(otherId);

        for (const Rating& r : otherRatings) {
            int movieId = r.getMovieId();
            double score = r.getScore();

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
            double finalScore = weightedSum[movieId] / weightSum[movieId];
            scoredMovies.push_back({movieId, finalScore});
        }
    }

    std::sort(scoredMovies.begin(), scoredMovies.end(),
        [](const std::pair<int, double>& a,
           const std::pair<int, double>& b) {
            if (a.second != b.second) {
                return a.second > b.second;
            }
            return a.first < b.first;
        });

    int limit = n;

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