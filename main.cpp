#include <iostream>
#include "MovieManager.h"

int main() {
    MovieManager mgr;

    Movie m1(1, "기생충", "드라마", 2019);
    Movie m2(2, "인터스텔라", "SF", 2014);
    Movie m3(3, "인셉션", "SF", 2010);

    m1.addRating(4.8);
    m1.addRating(5.0);

    m2.addRating(4.9);
    m3.addRating(4.7);

    mgr.addMovie(m1);
    mgr.addMovie(m2);
    mgr.addMovie(m3);

    std::cout << "=== 정렬 전 ===" << std::endl;
    mgr.printAll();

    Movie* found = mgr.findByTitle("기생충");
    if (found != nullptr) {
        std::cout << std::endl;
        std::cout << "=== 검색 결과 ===" << std::endl;
        std::cout << *found << std::endl;
    }

    mgr.sortByRating();

    std::cout << std::endl;
    std::cout << "=== 평점순 정렬 후 ===" << std::endl;
    mgr.printAll();

    return 0;
}