#pragma once
#include <boost/asio.hpp>

class Server {
 private:
  boost::asio::ip::tcp::acceptor acceptor_;

 public:
  Server(boost::asio::io_context& io_context, short port);

 private:
  void do_accept();
};
