#include "DisplayServer.h"

#include <iostream>
#include <limits>
#include <sstream>

DisplayServer::DisplayServer(std::uint16_t port, ValueHandler handler)
   : mAcceptor(mIoContext,
               asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
     mHandler(std::move(handler)) {
}

DisplayServer::~DisplayServer() {
   std::error_code error;
   mAcceptor.close(error);
   if (mSocket) {
      mSocket->close(error);
   }
}

void DisplayServer::Start() {
   Accept();
}

void DisplayServer::Poll() {
   mIoContext.poll();
}

void DisplayServer::Accept() {
   mSocket = std::make_shared<asio::ip::tcp::socket>(mIoContext);
   mAcceptor.async_accept(*mSocket, [this](const std::error_code& error) {
      if (error) {
         if (mAcceptor.is_open()) {
            std::cerr << "Could not accept display connection: "
                      << error.message() << std::endl;
            Accept();
         }
         return;
      }

      Read();
   });
}

void DisplayServer::Read() {
   asio::async_read_until(*mSocket, mBuffer, '\n',
      [this](const std::error_code& error, std::size_t) {
         if (error) {
            if (mAcceptor.is_open()) {
               Accept();
            }
            return;
         }

         std::istream input(&mBuffer);
         std::string command;
         unsigned int value = 0;
         input >> command >> value;

         if (command == "SET_VALUE" && !input.fail()) {
            mHandler(value);
         }

         Read();
      });
}
