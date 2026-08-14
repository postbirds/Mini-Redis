#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "KVDatabase.h"

// 출력을 위한 전역 자물쇠
std::mutex cout_mutex;


void threadTask(KVDatabase& db, int thread_id) {
    std::string key = "user_" + std::to_string(thread_id);

    db.set(key, "data");

    std::string result = db.get(key);

    // cout 독점 시작
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "[Thread " << thread_id << "] GET " << key << ": " << result << "\n"; 
    }
    // 자동 unlock


    std::cout << "[Thread " << thread_id << "] GET " << key << ": " << db.get(key) << "\n";
}

int main() {
    std::cout << "=== Mini-Redis 서버 시작 ===\n";
    KVDatabase db;
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; i++) {
        threads.emplace_back(threadTask, std::ref(db), i);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "=== 끝 == \n";

    return 0;
}
