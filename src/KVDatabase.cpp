#include "KVDatabase.h"

#include <fstream>
#include <iostream>
#include <mutex>

KVDatabase::KVDatabase() {
  load_snapshot();
}

KVDatabase::~KVDatabase() {
  std::cout << "[System] Server is shutting down. Backing up data...\r\n";
  save_snapshot();
}

void KVDatabase::set(const std::string& key, const std::string& value) {
  std::unique_lock<std::shared_mutex> lock(rw_mutex);

  store[key] = value;
  std::cout << "[SET] " << key << " = " << value << "\n";
}

std::string KVDatabase::get(const std::string& key) const {
  std::shared_lock<std::shared_mutex> lock(rw_mutex);

  auto it = store.find(key);
  if (it != store.end()) {
    return it->second;
  }
  return "(nil)";
}

bool KVDatabase::save_snapshot() const {
  std::shared_lock<std::shared_mutex> lock(rw_mutex);

  std::ofstream out(snapshot_file);
  if (!out.is_open())
    return false;

  for (const auto& [k, v] : store) {
    out << k << " " << v << "\r\n";
  }

  return true;
}

void KVDatabase::load_snapshot() {
  std::unique_lock<std::shared_mutex> lock(rw_mutex);

  std::ifstream in(snapshot_file);
  if (!in.is_open())
    return;

  std::string k, v;
  while (in >> k >> v) {
    store[k] = v;
  }

  std::cout << "[DB] Data restoration complete. Total:  " << store.size()
            << " keys.\r\n";
}
