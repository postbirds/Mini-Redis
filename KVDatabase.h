#pragma once             // 헤더 파일이 중복으로 포함되는 것을 막아준다.
#include <shared_mutex>  // 멀티스레드 락을 위해서 추가한다.
#include <string>
#include <unordered_map>

class KVDatabase {
 private:
  std::unordered_map<std::string, std::string> store;
  mutable std::shared_mutex rw_mutex;

  const std::string snapshot_file = "dump.rdb";

 public:
  KVDatabase();
  ~KVDatabase();

  void set(const std::string& key, const std::string& value);
  std::string get(const std::string& key) const;

  bool save_snapshot() const;
  void load_snapshot();
};
