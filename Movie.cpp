#include "Movie.h"
#include <iostream>

// 생성자: 기본 정보 입력 + 평점 정보는 처음에 0으로 시작
Movie::Movie(int id, const std::string& title,
             const std::string& genre, int year)
    : id(id), title(title), genre(genre),
      releaseYear(year), totalRating(0.0), ratingCount(0) {}

// getter들은 읽기 전용 함수이므로 const
int Movie::getId() const {
    return id;
}

std::string Movie::getTitle() const {
    return title;
}

std::string Movie::getGenre() const {
    return genre;
}

int Movie::getReleaseYear() const {
    return releaseYear;
}

// 평균 평점 계산
// 아직 평점이 하나도 없으면 0.0 반환
double Movie::getAverageRating() const {
    if (ratingCount == 0) return 0.0;
    return totalRating / ratingCount;
}

int Movie::getRatingCount() const {
    return ratingCount;
}

// 평점 추가
// 0.0 ~ 5.0 범위가 아니면 무시
void Movie::addRating(double r) {
    if (r < 0.0 || r > 5.0) return;
    totalRating += r;
    ratingCount++;
}

// 같은 영화인지 비교
// 제목과 개봉연도가 같으면 같은 영화로 판단
bool Movie::operator==(const Movie& o) const {
    return title == o.title && releaseYear == o.releaseYear;
}

// 정렬 기준
// 1차: 평균 평점 오름차순
// 2차: 제목 알파벳순
bool Movie::operator<(const Movie& o) const {
    if (getAverageRating() != o.getAverageRating()) {
        return getAverageRating() < o.getAverageRating();
    }
    return title < o.title;
}

// 출력 연산자 오버로딩
// cout << movie 형태로 자연스럽게 출력하기 위해 사용
std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.id << ". " << m.title
       << " (" << m.releaseYear << ")"
       << " [" << m.genre << "]"
       << "  평점: " << m.getAverageRating()
       << " (" << m.ratingCount << "건)";
    return os;
}