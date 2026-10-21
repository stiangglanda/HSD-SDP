#include "Address.h"

Address::Address(const std::string& street, std::size_t number, std::size_t zip, const std::string& city)
    : mStreet(street),
    mNumber(number),
    mZip(zip),
    mCity(city) {
}

const std::string& Address::GetStreet() const {
    return mStreet;
}

std::size_t Address::GetNumber() const {
    return mNumber;
}

std::size_t Address::GetZip() const {
    return mZip;
}

const std::string& Address::GetCity() const {
    return mCity;
}