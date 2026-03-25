#pragma once
#include <string>

class Rating {
private:
    std::string userId;
    int         movieId;
    double      score;

public:
    Rating();
    Rating(const std::string& userId,
           int movieId, double scoreInput);

    std::string getUserId() const;
    int         getMovieId() const;
    double      getScore() const;

    void display() const;
};