20231820 주재찬

# Movie Recommender

## 1. 프로젝트 개요

이 프로젝트는 C++로 구현한 영화 추천 프로그램입니다.
사용자, 영화, 평점 데이터를 CSV 파일에서 불러오고, 사용자 간 평점 패턴을 비교하여 영화를 추천합니다.

M3에서는 사용자 기반 협업 필터링 추천 기능을 구현했고, M4에서는 CSV 데이터 강화, 예외 처리, 장르별 추천 기능, Timer를 활용한 성능 측정, 코드 리팩토링을 추가했습니다.

---

## 2. 빌드 방법

프로젝트 루트 디렉토리에서 아래 명령어를 입력합니다.

```bash
make
```

빌드 결과 실행 파일은 `recommend`입니다.

빌드 결과물을 삭제하려면 아래 명령어를 사용합니다.

```bash
make clean
```

---

## 3. 실행 방법

```bash
make run
```

또는

```bash
./recommend
```

---

## 4. 주요 기능

### 영화 관리

* 영화 추가
* 제목으로 영화 검색
* 전체 영화 목록 출력
* 평점순 정렬 출력

### 사용자 관리

* 사용자 추가
* 사용자 목록 출력

### 평점 관리

* 사용자별 영화 평점 입력
* 영화별 평점 목록 조회

### 추천 기능

* 사용자 기반 협업 필터링 추천
* 유사 사용자 기반 영화 추천
* 장르별 영화 추천

### 파일 입출력

* `data/movies.csv`에서 영화 데이터 로드 및 저장
* `data/users.csv`에서 사용자 데이터 로드 및 저장
* `data/ratings.csv`에서 평점 데이터 로드 및 저장

---

## 5. 클래스 구조

### 데이터 클래스

* `Movie`
  영화 ID, 제목, 장르, 개봉 연도, 평균 평점 정보를 관리합니다.

* `User`
  사용자 ID, 이름, 이메일 정보를 관리합니다.

* `Rating`
  사용자 ID, 영화 ID, 평점 정보를 관리합니다.

### Manager 클래스

* `BaseManager`
  `loadFromFile`, `saveToFile`, `size`를 순수 가상 함수로 선언한 부모 클래스입니다.

* `MovieManager`
  영화 추가, 검색, 정렬, CSV 파일 입출력, 장르 필터 기능을 담당합니다.

* `UserManager`
  사용자 추가, 검색, CSV 파일 입출력을 담당합니다.

* `RatingManager`
  평점 추가, 사용자별 평점 조회, 영화별 평점 조회, CSV 파일 입출력을 담당합니다.

### 추천 관련 클래스

* `SimilarityCalculator`
  두 사용자의 평점 목록을 비교하여 유사도를 계산합니다.

* `Recommender`
  유사 사용자 탐색, 기본 영화 추천, 장르별 영화 추천 기능을 담당합니다.

* `Timer`
  RAII 방식으로 함수 실행 시간을 측정합니다.

---

## 6. 추천 알고리즘 설명

이 프로젝트는 사용자 기반 협업 필터링을 사용합니다.

추천 흐름은 다음과 같습니다.

1. 추천 받을 사용자의 평점 목록을 가져옵니다.
2. 다른 모든 사용자와 유사도를 계산합니다.
3. 유사도가 높은 상위 사용자를 선택합니다.
4. 유사 사용자가 높게 평가했고, 추천 대상 사용자가 아직 보지 않은 영화를 후보로 모읍니다.
5. 추천 점수를 계산하고 내림차순으로 정렬하여 상위 영화를 추천합니다.

유사도 공식은 다음과 같습니다.

```text
similarity = commonCount * 10 - scoreDiffSum
```

* `commonCount`: 두 사용자가 공통으로 평가한 영화 수
* `scoreDiffSum`: 공통 영화에 대한 평점 차이의 합

공통 영화가 없으면 비교할 근거가 없으므로 매우 낮은 값인 `-100.0`을 반환합니다.

---

## 7. M4 확장 기능

### 1) CSV 데이터 강화 및 예외 처리

M4에서는 추천 결과가 더 자연스럽게 나오도록 CSV 데이터를 강화했습니다.

* 영화 데이터 수 증가
* 사용자 데이터 수 증가
* 평점 데이터 수 증가
* 장르 분포 다양화
* 사용자별 취향 패턴이 드러나도록 평점 구성

또한 CSV 파일 입출력 과정에서 예외 처리를 추가했습니다.

* 파일을 열 수 없는 경우 `runtime_error` 발생
* CSV 한 줄의 형식이 잘못된 경우 해당 줄만 건너뛰고 계속 진행
* 잘못된 평점 값은 예외 처리

### 2) 장르별 영화 추천

기존 추천 기능은 전체 영화 중에서 추천을 수행했습니다.
M4에서는 사용자가 원하는 장르를 선택하면 해당 장르 안에서만 추천 영화를 제공하도록 확장했습니다.

예시:

```text
추천 받을 사용자 ID: u1
추천 받을 장르: 드라마
```

현재 등록된 영화 목록에서 장르 목록을 자동으로 추출하여 보여주기 때문에, 사용자는 존재하는 장르 중에서 선택할 수 있습니다.

### 3) Timer 성능 측정

`Timer` 클래스를 추가하여 추천 함수의 실행 시간을 측정했습니다.

적용한 함수 예시:

* `Recommender::recommend`
* `Recommender::recommendByGenre`
* `MovieManager::filterByGenre`

Timer는 생성자에서 시작 시간을 기록하고, 소멸자에서 경과 시간을 출력하는 RAII 방식으로 구현했습니다.

### 4) 리팩토링

M4에서는 코드 품질 개선을 위해 다음 리팩토링을 적용했습니다.

* 매직 넘버 상수화
* 추천 결과 출력 함수 분리
* 중복 출력 코드 제거
* 의미 있는 주석 추가

---

## 8. 실행 예시

### 기본 추천

```text
선택 > 9
추천 받을 사용자 ID: u1
```

### 장르별 추천

```text
선택 > 10
추천 받을 사용자 ID: u1
추천 받을 장르: 드라마
```

---

## 9. 프로젝트 구조

```text
Movie-Recommender/
├── data/
│   ├── movies.csv
│   ├── users.csv
│   └── ratings.csv
├── include/
│   ├── BaseManager.h
│   ├── Movie.h
│   ├── User.h
│   ├── Rating.h
│   ├── MovieManager.h
│   ├── UserManager.h
│   ├── RatingManager.h
│   ├── SimilarityCalculator.h
│   ├── Recommender.h
│   └── Timer.h
├── src/
│   ├── main.cpp
│   ├── Movie.cpp
│   ├── User.cpp
│   ├── Rating.cpp
│   ├── MovieManager.cpp
│   ├── UserManager.cpp
│   ├── RatingManager.cpp
│   ├── SimilarityCalculator.cpp
│   └── Recommender.cpp
├── Makefile
├── .gitignore
└── README.md
```

---
## 10. 작성자

숭실대학교 컴퓨터학부 주재찬
Movie Recommender Project

