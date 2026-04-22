#include "MovieManager.h"
#include <algorithm>
#include <iostream>

// 영화 추가
// 같은 영화(title + releaseYear 기준)는 중복 추가하지 않음
void MovieManager::addMovie(const Movie& movie) {
    for (const Movie& m : movies) {
        if (m == movie) {
            return;
        }
    }
    movies.push_back(movie);
}

// 제목으로 영화 검색
Movie* MovieManager::findByTitle(const std::string& title) {
    for (Movie& m : movies) {
        if (m.getTitle() == title) {
            return &m;
        }
    }
    return nullptr;
}

// ID로 영화 검색
Movie* MovieManager::findById(int id) {
    for (Movie& m : movies) {
        if (m.getId() == id) {
            return &m;
        }
    }
    return nullptr;
}

// 평점 기준 정렬
// Movie의 operator<를 사용
void MovieManager::sortByRating() {
    std::sort(movies.begin(), movies.end());
}

// 전체 영화 출력
// Movie의 operator<<를 사용
void MovieManager::printAll() const {
    if (movies.empty()) {
        std::cout << "등록된 영화가 없습니다." << std::endl;
        return;
    }

    for (const Movie& m : movies) {
        std::cout << m << std::endl;
    }
}

// 비어 있는지 확인
bool MovieManager::isEmpty() const {
    return movies.empty();
}