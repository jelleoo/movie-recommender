CXX = g++

# 컴파일 옵션
# -std=c++17 : C++17 표준 사용
# -Wall      : 경고 메시지 최대한 출력
# -g         : 디버깅 정보 포함
# -Iinclude  : 헤더 파일 탐색 경로 추가
CXXFLAGS = -std=c++17 -Wall -g -Iinclude

# 최종 실행 파일 이름
TARGET = recommend

# 오브젝트 파일 목록
OBJS = src/main.o src/Movie.o src/User.o src/Rating.o src/MovieManager.o src/UserManager.o src/RatingManager.o

# 기본 빌드 규칙
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# main.cpp 컴파일
src/main.o: src/main.cpp include/Movie.h include/User.h include/Rating.h include/MovieManager.h include/UserManager.h include/RatingManager.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

# Movie.cpp 컴파일
src/Movie.o: src/Movie.cpp include/Movie.h
	$(CXX) $(CXXFLAGS) -c src/Movie.cpp -o src/Movie.o

# User.cpp 컴파일
src/User.o: src/User.cpp include/User.h
	$(CXX) $(CXXFLAGS) -c src/User.cpp -o src/User.o

# Rating.cpp 컴파일
src/Rating.o: src/Rating.cpp include/Rating.h
	$(CXX) $(CXXFLAGS) -c src/Rating.cpp -o src/Rating.o

# MovieManager.cpp 컴파일
src/MovieManager.o: src/MovieManager.cpp include/MovieManager.h include/Movie.h
	$(CXX) $(CXXFLAGS) -c src/MovieManager.cpp -o src/MovieManager.o

# UserManager.cpp 컴파일
src/UserManager.o: src/UserManager.cpp include/UserManager.h include/User.h
	$(CXX) $(CXXFLAGS) -c src/UserManager.cpp -o src/UserManager.o

# RatingManager.cpp 컴파일
src/RatingManager.o: src/RatingManager.cpp include/RatingManager.h include/Rating.h
	$(CXX) $(CXXFLAGS) -c src/RatingManager.cpp -o src/RatingManager.o

# clean, run은 실제 파일이 아니라 명령어 이름
.PHONY: clean run

# 생성된 오브젝트 파일과 실행 파일 삭제
clean:
	rm -f $(OBJS) $(TARGET)

# 실행
run: $(TARGET)
	./$(TARGET)