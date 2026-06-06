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

    std::vector<Movie> filterByGenre(const std::string& genre) const;
    std::vector<std::string> getGenres() const;

    void sortByRating();
    void printAll() const;
    bool isEmpty() const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};