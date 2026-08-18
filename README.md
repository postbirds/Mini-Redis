# Mini-Redis

In-Memory Key-Value Storage 만들기

## 프로젝트 개요
- **개발 기간**: 2026.08.13 ~ 2026.08.
- **참여 인원**: 1인(개인 프로젝트)
- **목표**
	1. 반디소프트 취업
	2. 기존 Java 생태계를 C++ 메모리 관리, 멀티 스레딩, 비동기 IO 등을 이해하기 위함
	3. 웹 개발 및 업무 자동화에서는 컴퓨터과학 지식의 필요성을 크게 못 느낀 아쉬움 해소
- **기술 스택**
	- **IDE**: Visual Studio 2026 Community	
	- **Language:** C++20 (Compiler: MSVC)
	- **Network:** Boost.Asio
	- **Build & CI/CD:**: CMake, Docker, GitHub Actions
	- **Testing:** Google Test(GTest), AddressSanitizer(ASan)

## 실행 화면(Demo)
|get|set|
|:--:|:--:|
|<img src="./docs/resources/get.gif" width="400" height="200"/>|<img src="./docs/resources/set.gif" width="400" height="200"/>|

|save|저장 파일 확인|
|:--:|:--:|
|<img src="./docs/resources/save.gif" width="400" height="200"/>|<img src="./docs/resources/save_file.gif" width="400" height="200"/>|

## 프로젝트 실행 방법
### Local

> **전제조건:** Visual Studio 2026, [vcpkg](https://vcpkg.io), CMake 3.20+ 설치 필요

1. configure: `cmake -B build -S . -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"`
2. build: `cmake --build build --config Release`
3. run: `.\build\mini-redis.exe`

### Docker
1. 도커 이미지 빌드: `docker build -t my-redis:1.0 .`
2. 도커 컨테이너 실행: `docker run -d -p 6379:6379 --name mini-redis my-redis:1.0`

## 지원 명령어
|카테고리|커맨드|
|:--|:--|
|String|`SET <key> <value>`|
|String|`GET <key>`|
|Persistence|`SAVE`|


## 단계별 구현
 
- [x] C++, .clang-format, .clang-tidy, .editorconfig 등
- [x] 1단계: 자료구조 및 스레드 안정성
- [x] 2단계: Boost.Asio 네트워크 계층 연동
- [x] 3단계: Github Action CI (Linux 환경 자동 빌드, GTest, ASan 메모리 검증) 
- [x] 4단계: 💾 디스크 백업 기능
- [x] 5단계: 🐋 도커라이징


