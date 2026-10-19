//
// Created by stiangglanda on 2026-10-18.
//

#ifndef ADDRESS_H
#define ADDRESS_H
#include <string>

class Address {
public:
    Address(const std::string& street, size_t number, size_t zip, const std::string& city);
    std::string GetStreet() const;
    size_t GetNumber() const;
    size_t GetZip() const;
    std::string GetCity() const;
private:
    std::string mStreet;
    size_t mNumber;
    size_t mZip;
    std::string mCity;
};

#endif
