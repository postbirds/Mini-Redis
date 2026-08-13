#include "KVDatabase.h"
#include <iostream>
#include <mutex> // unique_lock, shared_lock 을 위해 필요하다.

void KVDatabase::set(const std::string& key, const std::string& value) {
	// 쓰기 락(독점 락 - 다른 모든 쓰기와 읽기 스레드를 대기시킨다)
	std::unique_lock<std::shared_mutex> lock(rw_mutex);

	store[key] = value;
	std::cout << "[SET] " << key << " = " << value << "\n";

	// 함수가 종료되는 지점에서 lock의 소멸자가 호출되며 자동으로 unlock()된다. (RAII 패턴)
}

std::string KVDatabase::get(const std::string& key) const {
	// 읽기 락(공유락 - 다른 읽기 스레드와 동시 접근이 가능하지만 쓰기는 대기 시킨다)
	std::shared_lock<std::shared_mutex> lock(rw_mutex);

	auto it = store.find(key);
	if (it != store.end()) {
		return it->second;
	}
	return "(nil)";
}