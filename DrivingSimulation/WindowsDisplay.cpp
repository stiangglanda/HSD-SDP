#include "WindowsDisplay.h"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

DisplayClient::DisplayClient(std::uint16_t port)
   : mSocket(mIoContext) {
   Init(port);
}

DisplayClient::~DisplayClient() {
   std::error_code error;
   mSocket.close(error);
}

bool DisplayClient::SendValue(unsigned int value) {
   return Send(value);
}


void DisplayClient::Init(std::uint16_t port) {
   asio::ip::tcp::resolver resolver(mIoContext);

   while (!mSocket.is_open()) {
      std::error_code error;
      const auto endpoints = resolver.resolve("127.0.0.1",
                                              std::to_string(port), error);
      if (!error) {
         asio::connect(mSocket, endpoints, error);
      }

      if (error) {
         std::cerr << "Display server on port " << port
                   << " is not online. Waiting..." << std::endl;
         std::this_thread::sleep_for(std::chrono::seconds(3));
      }
   }
}

bool DisplayClient::Send(unsigned int value) {
   const std::string message = "SET_VALUE " + std::to_string(value) + "\n";
   std::error_code error;

   asio::write(mSocket, asio::buffer(message), error);
   if (error) {
      std::cerr << "Could not send value to display: "
                << error.message() << std::endl;
      return false;
   }
   return true;
}
