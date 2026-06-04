#include "MovieManager.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

void MovieManager::addMovie(const Movie& movie) {      // 같은 영화가 중복으로 추가되지 않도록 Movie::operator==를 사용
    for (const Movie& m : movies) {                    // 아래의 m == movie 비교는 내부적으로 m.operator==(movie)를 호출
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
// movies 벡터 자체를 정렬
// 함수 호출 후 saveToFile()을 하면 정렬된 순서가 CSV에도 저장
// 정렬 결과를 유지하는 방식 선택
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
// 현재 CSV 파싱은 ','를 구분자로 사용함.
// 따라서 영화 제목이나 장르 안에 ','가 들어가는 경우는 고려하지 않음.
void MovieManager::loadFromFile(const std::string& filename) {
    movies.clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("영화 파일을 열 수 없습니다: " + filename);
    }

    std::string line;
    int lineNum = 0;

    std::getline(file, line); // 헤더 스킵
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
// 현재 메모리에 저장된 movies 벡터를 CSV 파일로 다시 저장.
// 프로그램 종료 시 최신 영화 목록이 data/movies.csv에 반영.
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