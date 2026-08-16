#pragma once
#include <boost/asio.hpp>

class KVDatabase;

class Server {
 private:
  boost::asio::ip::tcp::acceptor acceptor_;
  KVDatabase& db_;

 public:
  Server(boost::asio::io_context& io_context, short port, KVDatabase& db);

 private:
  void do_accept();
};
