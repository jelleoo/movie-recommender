#include <iostream>
#include <string>
#include <vector>

#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"

// 메뉴 출력 함수
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

    std::cout << "0. 종료" << std::endl;
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;
    RatingManager ratingMgr;

    // 프로그램 시작 시 CSV 파일에서 데이터 로드
    movieMgr.loadFromFile("data/movies.csv");
    userMgr.loadFromFile("data/users.csv");
    ratingMgr.loadFromFile("data/ratings.csv");

    // CSV에서 불러온 평점들을 Movie 객체의 평균 평점 계산에 다시 반영
    for (const Rating& r : ratingMgr.getRatings()) {
        Movie* foundMovie = movieMgr.findById(r.getMovieId());

        if (foundMovie != nullptr && r.getScore() != -1.0) {
            foundMovie->addRating(r.getScore());
        }
    }

    // 추천 기능을 담당하는 객체
    Recommender recommender(movieMgr, ratingMgr);

    int choice;

    while (true) {
        printMenu();
        std::cout << "선택 > ";
        std::cin >> choice;

        // 숫자가 아닌 입력 처리
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "숫자를 입력하세요." << std::endl;
            continue;
        }

        std::cin.ignore(1000, '\n');

        // 0. 종료
        if (choice == 0) {
            std::cout << "프로그램을 종료합니다." << std::endl;
            break;
        }

        // 1. 영화 추가
        else if (choice == 1) {
            int id, year;
            std::string title, genre;

            std::cout << "영화 ID: ";
            std::cin >> id;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(1000, '\n');

            std::cout << "제목: ";
            std::getline(std::cin, title);

            std::cout << "장르: ";
            std::getline(std::cin, genre);

            std::cout << "개봉 연도: ";
            std::cin >> year;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(1000, '\n');

            movieMgr.addMovie(Movie(id, title, genre, year));
            std::cout << "영화가 추가되었습니다." << std::endl;
        }

        // 2. 제목으로 검색
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

        // 3. 전체 영화 목록 출력
        else if (choice == 3) {
            std::cout << "=== 영화 목록 ===" << std::endl;
            movieMgr.printAll();
        }

        // 4. 평점순 정렬 출력
        else if (choice == 4) {
            movieMgr.sortByRating();

            std::cout << "=== 평점순 정렬 결과 ===" << std::endl;
            movieMgr.printAll();
        }

        // 5. 사용자 추가
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

        // 6. 사용자 목록 출력
        else if (choice == 6) {
            std::cout << "=== 사용자 목록 ===" << std::endl;
            userMgr.printAll();
        }

        // 7. 평점 입력
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
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(1000, '\n');

            Movie* foundMovie = movieMgr.findById(movieId);

            if (foundMovie == nullptr) {
                std::cout << "해당 ID의 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "평점(0.0 ~ 5.0): ";
            std::cin >> score;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(1000, '\n');

            Rating newRating(userId, movieId, score);

            if (newRating.getScore() == -1.0) {
                std::cout << "유효하지 않은 평점입니다." << std::endl;
                continue;
            }

            ratingMgr.addRating(newRating);
            foundMovie->addRating(newRating.getScore());

            std::cout << "평점이 입력되었습니다." << std::endl;
        }

        // 8. 영화별 평점 보기
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
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(1000, '\n');

            Movie* foundMovie = movieMgr.findById(movieId);

            if (foundMovie == nullptr) {
                std::cout << "해당 ID의 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "=== " << foundMovie->getTitle()
                      << " 평점 목록 ===" << std::endl;

            ratingMgr.printRatingsByMovieId(movieId);
        }

        // 9. 영화 추천 받기
        else if (choice == 9) {
            std::string targetUserId;
            int k, n;

            std::cout << "추천 받을 사용자 ID: ";
            std::getline(std::cin, targetUserId);

            if (userMgr.findById(targetUserId) == nullptr) {
                std::cout << "해당 ID의 사용자가 없습니다." << std::endl;
                continue;
            }

            std::cout << "유사 사용자 수 K: ";
            std::cin >> k;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cout << "추천 개수 N: ";
            std::cin >> n;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cout << "숫자를 입력하세요." << std::endl;
                continue;
            }

            std::cin.ignore(1000, '\n');

            if (k <= 0 || n <= 0) {
                std::cout << "K와 N은 1 이상의 숫자여야 합니다." << std::endl;
                continue;
            }

            std::vector<Movie> recommendations =
                recommender.recommend(targetUserId, k, n);

            if (recommendations.empty()) {
                std::cout << "추천할 영화가 없습니다." << std::endl;
                continue;
            }

            std::cout << "=== 추천 영화 목록 ===" << std::endl;

            for (const Movie& m : recommendations) {
                std::cout << m << std::endl;
            }
        }

        // 잘못된 메뉴 번호
        else {
            std::cout << "잘못된 메뉴 번호입니다." << std::endl;
        }
    }

    // 프로그램 종료 시 CSV 파일로 저장
    movieMgr.saveToFile("data/movies.csv");
    userMgr.saveToFile("data/users.csv");
    ratingMgr.saveToFile("data/ratings.csv");

    return 0;
}