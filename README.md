# Mini-Redis

In-Memory KVS 만들기

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
