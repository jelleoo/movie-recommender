#include "MovieManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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

// 특정 장르의 영화만 골라 반환한다.
// movies 벡터를 수정하지 않으므로 const 함수로 구현했다.
std::vector<Movie> MovieManager::filterByGenre(const std::string& genre) const {
    std::vector<Movie> result;

    for (const Movie& movie : movies) {
        if (movie.getGenre() == genre) {
            result.push_back(movie);
        }
    }

    return result;
}

// 현재 등록된 영화 목록에서 중복 없는 장르 목록을 만든다.
// CSV 데이터가 바뀌어도 장르 선택지가 자동으로 반영된다.
std::vector<std::string> MovieManager::getGenres() const {
    std::vector<std::string> genres;

    for (const Movie& movie : movies) {
        bool exists = false;

        for (const std::string& genre : genres) {
            if (genre == movie.getGenre()) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            genres.push_back(movie.getGenre());
        }
    }

    return genres;
}

// movies 벡터 자체를 정렬한다.
// 따라서 이 함수 호출 후 saveToFile()을 하면 정렬된 순서가 CSV에도 저장된다.
// 현재 구현은 정렬 결과를 유지하는 방식으로 선택했다.
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

// 현재 CSV 파싱은 ','를 구분자로 사용한다.
// 따라서 영화 제목이나 장르 안에 ','가 들어가는 경우는 고려하지 않았다.
// M4에서는 콤마가 없는 CSV 데이터를 사용한다고 가정한다.
void MovieManager::loadFromFile(const std::string& filename) {
    movies.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("영화 파일을 열 수 없습니다: " + filename);
    }

    std::string line;
    int lineNum = 0;

    std::getline(file, line);
    lineNum++;

    while (std::getline(file, line)) {
        lineNum++;

        if (line.empty()) {
            continue;
        }

        try {
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
        catch (const std::exception& e) {
            std::cerr << filename << " " << lineNum
                      << "번 줄 건너뜀: " << e.what() << std::endl;
        }
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