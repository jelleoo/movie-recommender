#include "MovieManager.h"
#include <algorithm>
#include <iostream>

void MovieManager::addMovie(const Movie& movie) {
    for (const Movie& m : movies) {
        if (m == movie) {
            return;
        }
    }
    movies.push_back(movie);
}

Movie* MovieManager::findByTitle(const std::string& title) {
    for (Movie& m : movies) {
        if (m.getTitle() == title) {
            return &m;
        }
    }
    return nullptr;
}

void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end());
}

void MovieManager::printAll() const {
    for (const Movie& m : movies) {
        std::cout << m << std::endl;
    }
}

bool MovieManager::isEmpty() const {
    return movies.empty();
}