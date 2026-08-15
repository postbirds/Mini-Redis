#pragma once

#include <boost/asio.hpp>
#include <memory>

class Session : public std::enable_shared_from_this<Session> {
 private:
  boost::asio::ip::tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];

 public:
  explicit Session(boost::asio::ip::tcp::socket socket);

  void start();

 private:
  void do_read();
  void do_write(std::size_t length);
};
