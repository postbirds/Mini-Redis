#include "Session.h"
#include <iostream>
#include <string>
#include "KVDatabase.h"

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket, KVDatabase& db)
    : socket_(std::move(socket)), db_(db) {}

void Session::start() {
  do_read();
}

void Session::do_read() {
  auto self(shared_from_this());

  boost::asio::async_read_until(
      socket_, buffer_, '\n',
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          std::string request{
              boost::asio::buffers_begin(buffer_.data()),
              boost::asio::buffers_begin(buffer_.data()) + length};

          buffer_.consume(length);

          response_ = process_command(request);
          do_write();
        }
      });
}

void Session::do_write() {
  auto self(shared_from_this());

  boost::asio::async_write(socket_, boost::asio::buffer(response_),
                           [this, self](boost::system::error_code ec,
                                        std::size_t bytes_transferred) {
                             if (!ec) {
                               do_read();
                             }
                           });
}

std::string Session::process_command(const std::string& input) {
  std::istringstream iss(input);
  std::string command, key, value;

  iss >> command;

  if (command == "SET" || command == "set") {
    iss >> key >> value;
    if (key.empty() || value.empty())
      return "-ERR syntax error\n";

    db_.set(key, value);
    return "+OK\n";
  } else if (command == "GET" || command == "get") {
    iss >> key;
    if (key.empty())
      return "-ERR syntax error\n";

    std::string res = db_.get(key);
    if (res == "(nil)")
      return "(nil)\n";
    return res + "\n";
  }

  return "-ERR unknown command\n";
}
