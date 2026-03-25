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
    ratings.push_back(Rating("winter2", 2, 4.9));
    ratings.push_back(Rating("jiselle3", 1, 5.0));
    ratings.push_back(Rating("ningning4", 3, 4.7));
    ratings.push_back(Rating("karina1", 3, 6.0));
    ratings.push_back(Rating("winter2", 3, 4.6));
    ratings.push_back(Rating("karina1", 4, 4.3));
    ratings.push_back(Rating("ningning4", 3, -1.0));


    for (int i = 0; i < (int)ratings.size(); i++) {
        if (ratings[i].getScore() == 0.0) continue;

        for (int j = 0; j < (int)movies.size(); j++) {
            if (movies[j].getId() == ratings[i].getMovieId()) {
                movies[j].addRating(ratings[i].getScore());
                break;
            }
        }
    }

    std::cout << "=== Movie List ===" << std::endl;
    for (int i = 0; i < (int)movies.size(); i++) {
        movies[i].display();
    }

    std::cout << std::endl;
    std::cout << "=== User List ===" << std::endl;
    for (int i = 0; i < (int)users.size(); i++) {
        users[i].display();
    }

    std::cout << std::endl;
    std::cout << "=== Rating List ===" << std::endl;
    for (int i = 0; i < (int)ratings.size(); i++) {
        ratings[i].display();
    }



    return 0;
}