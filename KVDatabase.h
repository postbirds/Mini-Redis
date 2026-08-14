#pragma once             // 헤더 파일이 중복으로 포함되는 것을 막아준다.
#include <shared_mutex>  // 멀티스레드 락을 위해서 추가한다.
#include <string>
#include <unordered_map>

class KVDatabase {
   private:
    std::unordered_map<std::string, std::string> store;

    // 읽기 쓰기 락
    // mutable 키워드는 const 함수(get) 안에서도 이 변수를 수정(lock)할 수 있게 한다.
    // 지금 1명이 읽고 있다는 상태를 기록해야하므로 수정이 가능해야 한다
    mutable std::shared_mutex rw_mutex;

   public:
    // .h파일에는 메서드의 껍데기(프로토타일)만 선언한다.
    void set(const std::string& key, const std::string& value);

    std::string get(const std::string& key) const;
};
