#pragma once
#include <vector>
#include <string>
#include "Movie.h"

// 영화 데이터를 관리하는 클래스
class MovieManager {
private:
    std::vector<Movie> movies;   // 영화 목록을 private으로 보관

public:
    // 영화 추가
    void addMovie(const Movie& movie);

    // 제목으로 영화 검색
    // 찾으면 해당 영화의 주소 반환, 못 찾으면 nullptr 반환
    Movie* findByTitle(const std::string& title);

    // ID로 영화 검색
    Movie* findById(int id);

    // 평점 기준 정렬
    void sortByRating();

    // 전체 영화 출력
    void printAll() const;

    // 비어 있는지 확인
    bool isEmpty() const;
};