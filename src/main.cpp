#include <iostream>
#include <string>
#include <vector>
#include <exception>

#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

constexpr int INPUT_IGNORE_LIMIT = 1000;
constexpr int DEFAULT_SIMILAR_USER_COUNT = 3;
constexpr int DEFAULT_RECOMMEND_COUNT = 5;

void printMenu() {
    std::cout << "\n=== Movie Recommender ===" << std::endl;

    std::cout << "[ 영화 ]" << std::endl;
    std::cout << "1. 영화 추가" << std::endl;
    std::cout << "2. 제목으로 검색" << std::endl;
    std::cout << "3. 전체 목록 출력" << std::endl;
    std::cout << "4. 평점순 정렬 출력" << std::endl;

    std::cout << "[ 사용자 ]" << std::endl;
    std::cout << "5. 사용자 추가" << std::endl;
    std::cout << "6. 사용자 목록 출력" << std::endl;

    std::cout << "[ 평점 ]" << std::endl;
    std::cout << "7. 평점 입력" << std::endl;
    std::cout << "8. 영화별 평점 보기" << std::endl;

    std::cout << "[ 추천 ]" << std::endl;
    std::cout << "9. 영화 추천 받기" << std::endl;
    std::cout << "10. 장르별 영화 추천 받기" << std::endl;

    std::cout << "0. 종료" << std::endl;
}

void printRecommendationList(const std::vector<Movie>& recommendations) {
    int rank = 1;

    for (const Movie& m : recommendations) {
        std::cout << rank << ". " << m.getTitle()
                  << " (" << m.getReleaseYear() << ")"
                  << " [" << m.getGenre() << "]"
                  << std::endl;

        rank++;
    }
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    try {
        movieMgr.loadFromFile("data/movies.csv");
    }
    catch (const std::exception& e) {
        std::cerr << "영화 데이터 로드 오류: " << e.what() << std::endl;
    }

    try {
        userMgr.loadFromFile("data/users.csv");
    }
    catch (const std::exception& e) {
        std::cerr << "사용자 데이터 로드 오류: " << e.what() << std::endl;
    }

    try {
        ratingMgr.loadFromFile("data/ratings.csv");
    }
    catch (const std::exception& e) {
        std::cerr << "평점 데이터 로드 오류: " << e.what() << std::endl;
    }

    for (const Rating& r : ratingMgr.getRatings()) {
        Movie* foundMovie = movieMgr.findById(r.getMovieId());

        if (foundMovie != nullptr && r.getScore() != -1.0) {
            foundMovie->addRating(r.getScore());
        }
    }

    Recommender recommender(movieMgr, ratingMgr);

    int choice;

    while (true) {
        printMenu();
        std::cout << "선택 > ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');
            std::cout << "숫자를 입력하세요." << std::endl;
            continue;
        }

        std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');

        if (choice == 0) {
            std::cout << "프로그램을 종료합니다." << std::endl;
            break;
        }
        else if (choice == 1) {
            int id, year;
            std::string title, genre;

            std::cout << "영화 ID: ";
            std::cin >> id;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');

            std::cout << "제목: ";
            std::getline(std::cin, title);

            std::cout << "장르: ";
            std::getline(std::cin, genre);

            std::cout << "개봉 연도: ";
            std::cin >> year;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');

            movieMgr.addMovie(Movie(id, title, genre, year));
            std::cout << "영화가 추가되었습니다." << std::endl;
        }
        else if (choice == 2) {
            std::string title;

            std::cout << "검색할 제목: ";
            std::getline(std::cin, title);

            Movie* found = movieMgr.findByTitle(title);

            if (found != nullptr) {
                std::cout << *found << std::endl;
            } else {
                std::cout << "해당 제목의 영화가 없습니다." << std::endl;
            }
        }
        else if (choice == 3) {
            std::cout << "=== 영화 목록 ===" << std::endl;
            movieMgr.printAll();
        }
        else if (choice == 4) {
            movieMgr.sortByRating();

            std::cout << "=== 평점순 정렬 결과 ===" << std::endl;
            movieMgr.printAll();
        }
        else if (choice == 5) {
            std::string id, name, email;

            std::cout << "사용자 ID: ";
            std::getline(std::cin, id);

            std::cout << "이름: ";
            std::getline(std::cin, name);

            std::cout << "이메일: ";
            std::getline(std::cin, email);

            userMgr.addUser(User(id, name, email));
            std::cout << "사용자가 추가되었습니다." << std::endl;
        }
        else if (choice == 6) {
            std::cout << "=== 사용자 목록 ===" << std::endl;
            userMgr.printAll();
        }
        else if (choice == 7) {
            std::string userId;
            int movieId;
            double score;

            if (userMgr.isEmpty()) {
                std::cout << "먼저 사용자를 추가하세요." << std::endl;
                continue;
            }

            if (movieMgr.isEmpty()) {
                std::cout << "먼저 영화를 추가하세요." << std::endl;
                continue;
            }

            std::cout << "사용자 ID: ";
            std::getline(std::cin, userId);

            User* foundUser = userMgr.findById(userId);

            if (foundUser == nullptr) {
                std::cout << "해당 ID의 사용자가 없습니다." << std::endl;
                continue;
            }

            std::cout << "영화 ID: ";
            std::cin >> movieId;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');

            Movie* foundMovie = movieMgr.findById(movieId);

            if (foundMovie == nullptr) {
                std::cout << "해당 ID의 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "평점(0.0 ~ 5.0): ";
            std::cin >> score;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');

            Rating newRating(userId, movieId, score);

            if (newRating.getScore() == -1.0) {
                std::cout << "유효하지 않은 평점입니다." << std::endl;
                continue;
            }

            ratingMgr.addRating(newRating);
            foundMovie->addRating(newRating.getScore());

            std::cout << "평점이 입력되었습니다." << std::endl;
        }
        else if (choice == 8) {
            int movieId;

            if (movieMgr.isEmpty()) {
                std::cout << "등록된 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "영화 ID: ";
            std::cin >> movieId;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(INPUT_IGNORE_LIMIT, '\n');

            Movie* foundMovie = movieMgr.findById(movieId);

            if (foundMovie == nullptr) {
                std::cout << "해당 ID의 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "=== " << foundMovie->getTitle()
                      << " 평점 목록 ===" << std::endl;

            ratingMgr.printRatingsByMovieId(movieId);
        }
        else if (choice == 9) {
            std::string targetUserId;

            std::cout << "추천 받을 사용자 ID: ";
            std::getline(std::cin, targetUserId);

            if (userMgr.findById(targetUserId) == nullptr) {
                std::cout << "해당 ID의 사용자가 없습니다." << std::endl;
                continue;
            }

            std::vector<Movie> recommendations =
                recommender.recommend(
                    targetUserId,
                    DEFAULT_SIMILAR_USER_COUNT,
                    DEFAULT_RECOMMEND_COUNT
                );

            if (recommendations.empty()) {
                std::cout << "추천할 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "=== 추천 영화 목록 ===" << std::endl;

            printRecommendationList(recommendations);
        }
        else if (choice == 10) {
            std::string targetUserId;
            std::string genre;

            std::cout << "추천 받을 사용자 ID: ";
            std::getline(std::cin, targetUserId);

            if (userMgr.findById(targetUserId) == nullptr) {
                std::cout << "해당 ID의 사용자가 없습니다." << std::endl;
                continue;
            }

            std::vector<std::string> genres = movieMgr.getGenres();

            if (genres.empty()) {
                std::cout << "등록된 장르가 없습니다." << std::endl;
                continue;
            }

            std::cout << "=== 선택 가능한 장르 ===" << std::endl;

            for (const std::string& g : genres) {
                std::cout << "- " << g << std::endl;
            }

            std::cout << "추천 받을 장르: ";
            std::getline(std::cin, genre);

            bool genreExists = false;

            for (const std::string& g : genres) {
                if (g == genre) {
                    genreExists = true;
                    break;
                }
            }

            if (!genreExists) {
                std::cout << "목록에 없는 장르입니다." << std::endl;
                continue;
            }

            std::vector<Movie> recommendations =
                recommender.recommendByGenre(
                    targetUserId,
                    genre,
                    DEFAULT_SIMILAR_USER_COUNT,
                    DEFAULT_RECOMMEND_COUNT
                );

            if (recommendations.empty()) {
                std::cout << "해당 장르에서 추천할 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "=== " << genre << " 장르 추천 영화 목록 ===" << std::endl;

            printRecommendationList(recommendations);
        }
        else {
            std::cout << "잘못된 메뉴 번호입니다." << std::endl;
        }
    }

    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    return 0;
}