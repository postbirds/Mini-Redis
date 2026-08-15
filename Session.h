#pragma once

#include <boost/asio.hpp>
#include <memory>

// 전방 선언 (의존성 최소화: 헤더 파일끼리 꼬이는 것 방지)
class KVDatabase;

class Session : public std::enable_shared_from_this<Session> {
 private:
  boost::asio::ip::tcp::socket socket_;
  KVDatabase& db_;

  boost::asio::streambuf buffer_;
  std::string response_;

 public:
  Session(boost::asio::ip::tcp::socket socket, KVDatabase& db);

  void start();

 private:
  void do_read();
  void do_write();
  std::string process_command(const std::string& input);
};
