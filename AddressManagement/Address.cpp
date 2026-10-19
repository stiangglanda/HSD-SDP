//
// Created by stiangglanda on 2026-10-18.
//

#include "Address.h"

Address::Address(const std::string& street, size_t number, size_t zip, const std::string& city)
    : mStreet(street),
      mNumber(number),
      mZip(zip),
      mCity(city) {
}

std::string Address::GetStreet() const {
    return mStreet;
}

size_t Address::GetNumber() const {
    return mNumber;
}

size_t Address::GetZip() const {
    return mZip;
}

std::string Address::GetCity() const {
    return mCity;
}
