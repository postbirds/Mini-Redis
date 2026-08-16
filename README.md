# Mini-Redis

In-Memory KVS 만들기

## 프로젝트 개요
- **개발 기간**: 2026.08.13 ~
- **참여 인원**: 1인(개인 프로젝트)
- **목표**
	1. 반디소프트 취업
	2. 기존 Java 생태계를 C++ 메모리 관리, 멀티 스레딩, 비동기 IO 등을 이해하기 위함
	3. 웹 개발 및 업무 자동화에서는 컴퓨터과학 지식의 필요성을 크게 못 느낀 아쉬움 해소
- **기술 스택**
	- **IDE**: Visual Studio 2026 Community	
	- **Language:** C++20
	- **Network:** Boost.Asio
	- **Build & CI/CD:**: CMake, Docker, GitHub Actions
	- **Testing:** Google Test(GTest), AddressSanitizer(ASan)

## 실행 화면(Demo)
|set/get|save|
|:--:|:--:|
|<img src="./docs/resources/" width="400" height="200"/>|<img src="./docs/resources/" width="400" height="200"/>|

|저장 파일 확인||
|:--:|:--:|
|<img src="./docs/resources/" width="400" height="200"/>|<img src="./docs/resources/" width="400" height="200"/>|

## 프로젝트 실행 방법
### Local
1. configure: `cmake -B out/build/x64-Release -S . -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_MAKE_PROGRAM="C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja\ninja.exe"`
2. build: `cmake --build out/build/x64-Release --config Release`


### Docker
1. 도커 이미지 빌드: `docker build -t my-redis:1.0 .`
2. 도커 컨테이너 실행: `docker run -d -p 6379:6379 --name mini-redis my-redis:1.0`

## 핵심 기술 및 구현 개념

## 개발 및 학습 문서(Tech Docs)







## 무작위 작성 중

1. [Visual Studio Community 2026 설치](https://visualstudio.microsoft.com/ko/)

- 워크로드 선택: Desktop development with C++
- 이 워크로드를 선택해 C++ 컴파일러(MSVC)와 기본 표준 라이브러리들이 설치된다.

2. '콘솔 앱' 프로젝트 생성




## 언어

`void set(const std::string& key, const std::string& value);`
&(앰퍼샌드): 참조자(Reference)
자바의 경우 void set(String key)를 호출하면 문자열 객체의 '주소값'만 넘겨준다.
C++의 경우 void set(std::string key)라고 쓰면, C++은 변수를 통째로 복사(Deep Copy)해서 새로운 문자열을 하나 더 만든다.
만약 넘어오는 문자열이 10MB짜리라면, 함수를 호출할 때마다 10MB짜리 복사본이 메모리에 더 생기므로 낭비가 된다.

이 복사 비용을 없애기 위해 등장한 것이 참조자(&)이다. &를 타입 뒤에 붙이면, 새로운 변수를 만드는 대신 "원본 변수에 별명(Alias)을 붙여서 그대로 쓴다"는 뜻이 된다. 원본 메모리를 그대로 가리키므로 복사 비용이 '0'이다.

const는 자바의 final과 비슷하다. Read-Only로 한 번 초기화 되면 그 변수는 그 이후 값을 바꿀 수 없다.


지금까지 위 내용에서 진행한 것
1단계: 코어 자료구조 및 스레드 안정성 확보


## 메모용
2단계: 네트워크 계층 연동
진짜 서버처럼 켜져 있으면서 외부 파이썬 스크립트나 터미널(Telnat)에서 보내는 패킷을 받아 처리한다.
C++ 네트워크 프로그래밍의 실질적 표준인 Boost.Asio 라이브러리를 도입하여, 성능 저하 없이 수 많은 접속자를 비동기(Async)로 처리하는 법을 배운다.

3단계: RAII 패턴 및 백업 기능
서버가 갑자기 꺼지게 되면 메모리에 있던 데이터가 날아간다. 이를 방지하기 위해 디스크(파일)에 데이터를 백업하는 기능을 만든다.
자바의 try-with-resoruces나 finally 블록 없이, C++ 고유의 RAII 패턴을 활용해 예외가 발생해도 파일 스트림과 락이 100% 안전해진다.





자바는 pom.xml이나 build.gradle에 이름만 적으면 maven Central에서 알아서 다운로드하고 클래스 패스도 연결해준다.
하지만, C++은 역사적으로 중앙 집중식 시스템이 없어서 개발자가 직접 소스코드를 다운받고, 컴파일하고, 링커 경로에 수동 지정해준다.
다행히도 최근 MS가 만든 vcpkg 라는 패키지 매니저가 등장해서 자바의 Maven 처럼 아주 편하게 외부 라이브러리를 사용할 수 있게 되었다.
vcpkg를 설치하고 Boost.Asio를 설치하자. 

https://learn.microsoft.com/ko-kr/vcpkg/get_started/get-started?pivots=shell-powershell

```
# 1. C드라이브 최상단(또는 원하는 개발 폴더)으로 이동
cd C:\

# 2. vcpkg 저장소 클론 (깃허브에서 가져오기)
git clone https://github.com/microsoft/vcpkg.git

# 3. vcpkg 폴더로 이동
cd vcpkg

# 4. vcpkg 실행 파일 생성 (부트스트랩)
.\bootstrap-vcpkg.bat
```
```
# vcpkg 폴더 안에서 실행
.\vcpkg integrate install

```
```
$env:VCPKG_ROOT = "C:\path\to\vcpkg"
$env:PATH = "$env:VCPKG_ROOT;$env:PATH"
```
```
vcpkg new --application
```
위를 수행하면 vcpk.json과 vcpk-configuration.json이 나온다.
vcpkg.json는 설치한 라이브러리 이름과 버전 정보가 기록된다.
vcpk-configuration.json은 라이브러리를 어디서 다운로드할지 패키지 매니저의 상세 설정이 적혀있다.
과거 C++을 사용할 때는 개발자가 직접 vcpk install ... 을 해야했지만, 이 파일들이 있음으로서 리눅스나 다른 개발자 컴퓨터에서 명령어를 하나하나 칠 필요 없지 CMake가 빌드될 때 알아서 vckg.json을 읽고 라이브러리를 싹 다운로드 한다.

vcpkg add port boost-asio

이후 vcpkg install 명령어를 수행하면 vcpk.json에 적힌 목록을 읽어와 자동으로 설치를 진행한다.



- shared_from_this()는 GC를 대체한다. 자바는 비동기 작업이 끝날 때까지 객체가 메모리에 살아있도록 GC가 관리해준다. 하지만 C++은 냅두면 메모리에서 삭제(Segfault 에러 발생)된다. auto self(shared_from_this());는 네트워크 통신이 끝날 때까지 Session(자신)의 메모리 수명을 연장시켜줘라는 스마트 포인터 기법이다.

- std::move(이동 의미론): 소켓 객체처럼 운영체제 자원을 가지고 있는 무거운 객체는 복사하면 안된다. std::move는 자바에 없는 개념으로 메모리 복사 없이 소유권만 통째로 다음 객체(Session)에 넘기는 극한의 최적화 기법이다.

- io_context(이벤트 루프): 자바 Netty의 EventLoopGroup과 동일하다. run()을 호출하면 무한 루프르 돌며 운영체제로부터 네트워크 신호를 받아 등록된 람바 함수들을 실행한다.

KVDatabase(GET/SET)로직과 네트워크(Boost.Asio)를 결합해 진짜 텍스트 명령어를 처리하는 Redis처럼 만들기 위해서는 어떻게 해야할까?

스프링에서는 @Autowired로 빈을 주입받는데 C++에서는 공유 데이터를 여러 세션이 어떻게 공유한가? C++에서는 아주 직관적으로 참조자(&)를 사용한 의존성 주입 방식을 사용한다. main함수에서 KVDatabsae를 딱 하나 만들고, 그 참조(주소)를 Server를 거쳐 각 Session에게 전달해주면 된다.

---
C++ 비동기 네트워크 개발 시 '주의해야 할 함정'
Session 클래스에서 std::string response_;를 선언해두었다.
그냥 do_read 함수 안에서 string response를 만들어서 바로 보내면 안되나?라고 생각할 수도 있다.

자바에서는 가능하지만, C++에서는 안된다.

async_write는 이름 그대로 Async이다. 이문자열 좀 네트워크로 전송해줘라고 운영체제에 부탁만하고, 함수는 곧바로 종료된다.
지역 변수로 

[3단계] 서버가 꺼져도 데이터가 유지되는 영속성(Persistence)을 가진 데이터베이스를 만들자
지금까지는 메모리 기반에서 한 것이다.
데이터가 꺼져도 유지되게 하기 위해서 C++에서는 RAII(Resource Acquisition Is Initialization) 패턴으로 간단한 코드로 작성할 수 있다.
참고로 자바에서는 파일을 열고 닫을 때 try-with-resources를 사용해야했다.

[4단계] CMake로 Build
자바는 IDE의 build 버튼을 눌러 .jar 파일을 뽑으면 된다. 윈도우, 리눅스, 맥북 등 JVM위에서 동일하게 돌아간다.
하지만, C++에서는 다르다.

지금까지 작성한 C++ 코드는 내 윈도우 컴퓨터의 Visual Studio 2026에서만 켜진다.
- C++은 소스코드를 OS와 CPU가 알아듣는 native code(기계어)로 번역한다.
- 윈도우에서 만든 .exe  파일은 리눅스나 맥에서는 실행되지 않는다.
- 현재 만든 서비스를 실제로 배포하려면 리눅스 환경에 올려야 하고, 그러려면 리눅스 환경에서 코드를 다시 컴파일(빌드) 해야한다.
- 문제는 리눅스는 Visual Studio도 없고, .sln(솔루션 파일)이나 .vcxproj(프로젝트) 파일을 읽을 수도 없다.

따라서, C++계의 Maven/Gradle인 CMake가 등장했다.
자바 프로젝트의 모든 설정(의존성 파일, 컴파일 옵션 등)을 pom.xml이나 build.gradle에 적는 것처럼
C++에선 CMakeLists.txt 라는 메모장 파일 하나에 프로젝트의 모든 정보를 적어둔다.

CMake는 이 메모장 파일을 읽고, 현재 컴퓨터 환경에 맞춰 빌드용 설계도로 자동 변환해준다.
- 윈도우 개발자가 CMake를 실행하면 .sln (솔루션파일)을 만들어 준다.
- 리눅스 서버에서 CMake를 실행하면 Makefile(리눅스용 빌드 스크립트)을 만든다.
- Macm 개발자가 CMake를 실행하면 .xcodeproj (Xcode용 프로젝트 파일)을 만들어 준다.

CMake를 적용한다는 것은 내 코드를 "어떤 OS, 어떤 에디터(VS, CLionn, VS Code)를 쓰건 1초만에 똑같은 세팅으로 빌드할 수 있는 글로벌 표준 형태를 만다는 것이다.

CMake로 빌드해보기 위해서
1. Configure
- vcpkg 패키지 매니저 경로를 CMake에 알려주어서 Boost 라이브러를 자동으로 찾게 한다.
```
# (주의: vcpkg를 C:\vcpkg 에 설치했다고 가정한 명령어입니다. 경로가 다르다면 수정해 주세요.)
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="C:\vcpkg\scripts\buildsystems\vcpkg.cmake"
```
-B build: 빌드결과물은 섞이지 않도록 build라는 새로운 폴더를 만들어 그 안에 넣어줘
- S . : 소스코드와 CMakeLists.txt는 현재 폴더(.)에 있따.

이 명령어를 치면 build 폴더가 생기고, 그 안에 수많은 컴파일 설정 파일들이 자동으로 생성된다.

2단계: 실제 컴파일 실행(build)
이제 생성된 설정 파일을 바탕으로 진짜 .exe 파일을 뽑아낸다.
cmake --build build
빌드가 성공적으로 끝나면 build/Debug/ 폴더 등 안에 MiniRedis.exe 파일이 있다.


## C++을 도커라이징하자.
C++을 도커라이징하기 위해서 멀티 스테이지 빌드를 적용해 Dockerfile을 작성해야 한다.

자바는 소스코드 빌드할 때 JDK가 필요하지만 실행할 때는 가벼운 JRE만 있으면 된다.
C++도 마찬가지이다.
- Stage1 (빌더): 무거운 C++ 컴파일러(GCC/Clang)와 CMake, 라이브러리를 설치하여 소스코드를 .exe(리눅스에선 바이너리 실행파일)로 변환한다.
- Stage2 (런타임): 컴파일러는 전부 버리고, 아주 가벼운 빈 리누긋 OS에 방금 만든 '실행 파일 딱 1개'만 옮겨 담아서 최종 컨테이너를 만든다.
이렇게 함으로써, 컨테이너 용량이 기가바이트 단위에서 메가바이트 단위로 줄어든다.

dockerfile 작성 후
1. 도커 이미지 빌드(포장하기) `docker build -t mini-redis:1.0`
-  중간에 실패했을 때는 docker build --no-cache -t mini-redis:1.0 .으로 다시 해보는 게 좋다.
2. docker 실행: `docker run -d -p 6379:6379 --name my-redis mini-redis:1.0`
3. 이렇게 하고 터미널에서 telnet 127.0.0.1 6379로 접속해서 SET name docker 등을 수행할 수 있다.



Dockerfile에서는 vcpkg를 사용하지 않고 리눅스의 apt-get install libboost-dev를 사용했다.
그런데, 소스코드 자체는 수정하지 않았다. find_package(Boost REQUIRED) 덕분에 윈도우에서는 vcpkg 폴더를 찾고, linux에선 os 표준 라이브러리르 뒤져서 알아서 한다.

## Test
gTest 설치 및 test_kvdatabase.cpp 작성 (테스트하기)
Test 코드 파일에는 main()함수가 없으므로 gtest에서 제공하는  gtest_main을 링크해서 이 파일만을 위한 전용 실행 파일을 만들어야 한다.
CMakeLists.txt를 추가해야한다.


## GitHub Actions로 자동 배포 파이프라인 CICD만들기






## Visual Studio
VS에서 솔루션 탐색기에서는 .cpp나 .h 같은 소스 파일만 보인다. 파일을 구조화 해주는 점에서는 장점이지만, 다른 파일들을 수정하고자 할 때 매번 전체 파일을 봐야하는 것에 불편함이 있다.
이를 해결하기 위해서 솔루션 탐색기 맨 위의 솔루션 '이름'을 마우스 우클릭해서 추가 > 기존항목으로 추가하는 게 좋다.
이렇게 하면 솔루션 탐색기에 Solution Items 라는 가상 폴더가 생기면서 지정한 파일들만 들어온다. 




