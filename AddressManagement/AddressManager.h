#ifndef ADDRESSMANAGER_H
#define ADDRESSMANAGER_H
#include <string>
#include <vector>
#include "Reader.h"
#include "Writer.h"
#include "Person.h"
#include "Address.h"

class AddressManager {
public:
    void ReadFile(std::string path, Reader rdr);
    void WriteAddresses(std::string path, Writer wrt);
    void AddPerson();
    void AddAddress();
    void GetAddress(size_t index);
    void GetPerson(size_t index);
private:
    std::vector<Person> mPersons;
    std::vector<Address> mAddresses;
};

#endif
