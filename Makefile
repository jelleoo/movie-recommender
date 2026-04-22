
CXX = g++

# 컴파일 옵션
# -std=c++17 : C++17 표준 사용
# -Wall      : 경고 메시지 최대한 출력
# -g         : 디버깅 정보 포함
CXXFLAGS = -std=c++17 -Wall -g

# 최종 실행 파일 이름
TARGET = movie_recommender

# 오브젝트 파일 목록
OBJS = main.o Movie.o User.o Rating.o MovieManager.o UserManager.o RatingManager.o

# 기본 빌드 규칙
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# main.cpp 컴파일
main.o: main.cpp Movie.h User.h Rating.h MovieManager.h UserManager.h RatingManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Movie.cpp 컴파일
Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c Movie.cpp

# User.cpp 컴파일
User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

# Rating.cpp 컴파일
Rating.o: Rating.cpp Rating.h
	$(CXX) $(CXXFLAGS) -c Rating.cpp

# MovieManager.cpp 컴파일
MovieManager.o: MovieManager.cpp MovieManager.h Movie.h
	$(CXX) $(CXXFLAGS) -c MovieManager.cpp

# UserManager.cpp 컴파일
UserManager.o: UserManager.cpp UserManager.h User.h
	$(CXX) $(CXXFLAGS) -c UserManager.cpp

# RatingManager.cpp 컴파일
RatingManager.o: RatingManager.cpp RatingManager.h Rating.h
	$(CXX) $(CXXFLAGS) -c RatingManager.cpp

# make clean, make run은 실제 파일이 아니라 명령어 이름이라고 알려줌
.PHONY: clean run

# 생성된 오브젝트 파일과 실행 파일 삭제
clean:
	rm -f $(OBJS) $(TARGET)

# 실행 파일 실행
run: $(TARGET)
	./$(TARGET)