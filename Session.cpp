#include "Session.h"
#include <iostream>
#include <string>

using boost::asio::ip::tcp;

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

void Session::start() {
  std::cout << "[New Client] IP: "
            << socket_.remote_endpoint().address().to_string() << "\n";
  do_read();
}

void Session::do_read() {
  auto self(shared_from_this());

  socket_.async_read_some(
      boost::asio::buffer(data_, max_length),
      [this, self](boost::system::error_code ec, std::size_t length) {
        if (!ec) {
          std::cout << "[RECV] " << std::string(data_, length);
          do_write(length);
        }
      });
}

void Session::do_write(std::size_t length) {
  auto self(shared_from_this());

  boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
                           [this, self](boost::system::error_code ec,
                                        std::size_t bytes_transferred) {
                             if (!ec) {
                               do_read();
                             }
                           });
}
