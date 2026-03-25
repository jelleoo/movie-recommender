#include <iostream>
#include <vector>
#include "Movie.h"
#include "User.h"
#include "Rating.h"

int main() {
    std::vector<Movie> movies;
    std::vector<User> users;
    std::vector<Rating> ratings;

    movies.push_back(Movie(1, "기생충", "드라마", 2019));
    movies.push_back(Movie(2, "인터스텔라", "SF", 2014));
    movies.push_back(Movie(3, "인셉션", "SF", 2010));
    movies.push_back(Movie(4, "어벤져스", "액션", 2012));

    users.push_back(User("karina1", "카리나", "karina@gmail.com"));
    users.push_back(User("winter2", "윈터", "winter@naver.com"));
    users.push_back(User("jiselle3", "지젤", "jiselle@daum.net"));
    users.push_back(User("ningning4", "닝닝", "ningning@gmail.com"));
    
    
    ratings.push_back(Rating("karina1", 4, 4.8)); 
    ratings.push_back(Rating("winter2", 2, 0.0));
    ratings.push_back(Rating("jiselle3", 1, 5.0));
    ratings.push_back(Rating("ningning4", 3, 4.7));
    ratings.push_back(Rating("karina1", 3, 6.0));
    ratings.push_back(Rating("karina1", 4, 4.3));
    ratings.push_back(Rating("ningning4", 3, -1.0));
    ratings.push_back(Rating("jiselle3", 2, 4.5));


    for (const Rating& r : ratings) {
        if (r.getScore() == -1.0) continue;

        for (Movie& m : movies) {
            if (m.getId() == r.getMovieId()) {
                m.addRating(r.getScore());
                break;
            }
        }
    }

    std::cout << "=== 영화 목록 ===" << std::endl;
    for (const Movie& m : movies) {
        m.display();
    }

    std::cout << std::endl;
    std::cout << "=== 사용자 목록 ===" << std::endl;
    for (const User& u : users) {
        u.display();
    }

    std::cout << std::endl;
    std::cout << "=== 평점 목록 ===" << std::endl;
    for (const Rating& r : ratings) {
        r.display();
    }



    return 0;
}