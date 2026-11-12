#ifndef DISPLAY_CLIENT_H
#define DISPLAY_CLIENT_H

#include <asio.hpp>
#include <cstdint>
#include <memory>

#include "Object.h"

class DisplayClient : public Object {
public:   
   ~DisplayClient() override;

   bool SendValue(unsigned int value);
   using SPtr = std::shared_ptr<DisplayClient>;
protected:
   DisplayClient(std::uint16_t port);
   DisplayClient(DisplayClient const&) = delete;
   DisplayClient& operator=(DisplayClient const&) = delete;

private:
   asio::io_context mIoContext;
   asio::ip::tcp::socket mSocket;

   void Init(std::uint16_t port);
   bool Send(unsigned int value);
};



class DigitalDisplay: public DisplayClient {
public:
   DigitalDisplay(): DisplayClient(4711) {
   }
};


class AnalogDisplay: public DisplayClient {
public:
   AnalogDisplay(): DisplayClient(4712) {
   }
};

#endif //DISPLAY_CLIENT_H
