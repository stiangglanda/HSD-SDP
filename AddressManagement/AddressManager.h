#ifndef ADDRESSMANAGER_H
#define ADDRESSMANAGER_H
#include <string>
#include <vector>
#include "Reader.h"
#include "Person.h"
#include "Address.h"

class Writer;

class AddressManager {
public:
    void ReadFile(const std::string& path, Reader rdr);
    void WriteAddresses(const std::string& path, Writer& wrt);
    void AddPerson(const Person& person);
    void AddAddress(const Address& address);
    void GetAddress(size_t index);
    void GetPerson(size_t index);
    size_t GetAddressCount() const;
private:
    std::vector<Person> mPersons;
    std::vector<Address> mAddresses;
};

#endif
