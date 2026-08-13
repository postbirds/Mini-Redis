#pragma once // 헤더 파일이 중복으로 포함되는 것을 막아준다.
#include <string>
#include <unordered_map>

class KVDatabase
{
private:
	std::unordered_map<std::string, std::string> store;

public:
	// .h파일에는 메서드의 껍데기(프로토타일)만 선언한다.
	void set(const std::string& key, const std::string& value);
	std::string get(const std::string& key);

};

