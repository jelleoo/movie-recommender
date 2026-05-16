#pragma once
#include <vector>
#include <string>
#include "Movie.h"
#include "BaseManager.h"

class MovieManager : public BaseManager {
private:
    std::vector<Movie> movies;

public:
    void addMovie(const Movie& movie);
    Movie* findByTitle(const std::string& title);
    Movie* findById(int id);
    void sortByRating();
    void printAll() const;
    bool isEmpty() const;

    // BaseManager에서 상속받은 순수 가상 함수 구현
    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};