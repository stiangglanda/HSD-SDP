#ifndef WRITER_H
#define WRITER_H
#include <fstream>
#include <string>
#include "Address.h"
#include "Person.h"

class AddressManager;

class Writer {
public:
    virtual ~Writer() = default;
    virtual void WriteHeader(std::ofstream & out) = 0;
    virtual void WriteFooter(std::ofstream & out) = 0;
    virtual void WriteAddress(std::ofstream & out, const Address& address) = 0;
    virtual void WritePerson(std::ofstream & out, const Person& person) = 0;

    void Write(const std::string& path, AddressManager& man);
};

#endif
