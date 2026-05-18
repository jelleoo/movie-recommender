#pragma once
#include <vector>
#include <string>
#include <utility>
#include "Movie.h"
#include "MovieManager.h"
#include "RatingManager.h"

class Recommender {
private:
    MovieManager& movieMgr;
    RatingManager& ratingMgr;

public:
    Recommender(MovieManager& movieMgr, RatingManager& ratingMgr);

    std::vector<std::pair<std::string, double>> findSimilarUsers(
        const std::string& targetUserId, int k) const;

    std::vector<Movie> recommend(
        const std::string& targetUserId, int k, int n) const;
};