#include "Server.h"
#include "Session.h"

using boost::asio::ip::tcp;

Server::Server(boost::asio::io_context& io_context, short port, KVDatabase& db)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), db_(db) {
  do_accept();
}

void Server::do_accept() {
  acceptor_.async_accept(
      [this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
          std::make_shared<Session>(std::move(socket), db_)->start();
        }
        do_accept();
      });
}
