#include <iostream>
#include <string>
#include "MovieManager.h"
#include "UserManager.h"

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
    std::cout << "0. 종료" << std::endl;
}

int main() {
    MovieManager movieMgr;
    UserManager userMgr;

    int choice;

    while (true) {
        printMenu();
        std::cout << "선택 > ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "숫자를 입력하세요." << std::endl;
            continue;
        }

        std::cin.ignore(1000, '\n');

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
        
    }

    return 0;
}