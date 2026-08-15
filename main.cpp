#include <boost/asio.hpp>
// #include <Windows.h>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include "Server.h"

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
    std::cout << "[Thread " << thread_id << "] GET " << key << ": " << result
              << "\n";
  }
  // 자동 unlock
}

void threadTaskMain() {
  SetConsoleOutputCP(CP_UTF8);

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
}

int main() {
  try {
    std::cout << "=== Mini-Redis Async Server Started (Port 6379) ===\n";

    // io_context: Asio의 심장. 운영체제의 네트워크 이벤트를 관리하는 루프
    boost::asio::io_context io_context;

    // 6379(Redis 기본 포트) 포트로 서버를 연다.
    Server server(io_context, 6379);

    // 이벤트 루프 실행 (블로킹되며, 접속이나 메시지가 올 때마다 콜백을 실행한다)
    io_context.run();

  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
