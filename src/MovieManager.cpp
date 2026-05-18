#include "MovieManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

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

Movie* MovieManager::findById(int id) {
    for (Movie& m : movies) {
        if (m.getId() == id) {
            return &m;
        }
    }
    return nullptr;
}

void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end());
}

void MovieManager::printAll() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    for (const Movie& m : movies) {
        std::cout << m << std::endl;
    }
}

bool MovieManager::isEmpty() const {
    return movies.empty();
}

void MovieManager::loadFromFile(const std::string& filename) {
    movies.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 열 수 없습니다." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // 헤더 스킵

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        int id, year;
        std::string title, genre;

        std::getline(ss, token, ',');
        id = std::stoi(token);

        std::getline(ss, title, ',');
        std::getline(ss, genre, ',');

        std::getline(ss, token, ',');
        year = std::stoi(token);

        addMovie(Movie(id, title, genre, year));
    }

    file.close();
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: " << filename << " 저장 실패" << std::endl;
        return;
    }

    file << "id,title,genre,releaseYear" << std::endl;

    for (const Movie& m : movies) {
        file << m.getId() << ","
             << m.getTitle() << ","
             << m.getGenre() << ","
             << m.getReleaseYear() << std::endl;
    }

    file.close();
}

int MovieManager::size() const {
    return (int)movies.size();
}