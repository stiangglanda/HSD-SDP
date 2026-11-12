#ifndef DISPLAY_SERVER_H
#define DISPLAY_SERVER_H

#include <asio.hpp>

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

class DisplayServer {
public:
   using ValueHandler = std::function<void(unsigned int)>;

   DisplayServer(std::uint16_t port, ValueHandler handler);
   ~DisplayServer();

   void Start();
   void Poll();

private:
   void Accept();
   void Read();

   asio::io_context mIoContext;
   asio::ip::tcp::acceptor mAcceptor;
   std::shared_ptr<asio::ip::tcp::socket> mSocket;
   asio::streambuf mBuffer;
   ValueHandler mHandler;
};

#endif //DISPLAY_SERVER_H
