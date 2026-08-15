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
	- **Language:** C++20
	- **Network:** Boost.Asio
	- **Build & CI/CD:**: CMake, Docker, GitHub Actions
	- **Testing:** Google Test(GTest), AddressSanitizer(ASan)

## 실행 화면(Demo)
GIF 파일을 넣자

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



## Visual Studio
VS에서 솔루션 탐색기에서는 .cpp나 .h 같은 소스 파일만 보인다. 파일을 구조화 해주는 점에서는 장점이지만, 다른 파일들을 수정하고자 할 때 매번 전체 파일을 봐야하는 것에 불편함이 있다.
이를 해결하기 위해서 솔루션 탐색기 맨 위의 솔루션 '이름'을 마우스 우클릭해서 추가 > 기존항목으로 추가하는 게 좋다.
이렇게 하면 솔루션 탐색기에 Solution Items 라는 가상 폴더가 생기면서 지정한 파일들만 들어온다. 
