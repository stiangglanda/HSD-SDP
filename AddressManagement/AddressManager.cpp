#include "AddressManager.h"
#include "Writer.h"

void AddressManager::ReadFile(const std::string& path, Reader rdr) {
}

void AddressManager::WriteAddresses(const std::string& path, Writer& wrt) {
    wrt.Write(path, *this);
}

void AddressManager::AddPerson(const Person& person) {
    mPersons.push_back(person);
}

void AddressManager::AddAddress(const Address& address) {
    mAddresses.push_back(address);
}

const Address& AddressManager::GetAddress(size_t index) {
    return mAddresses.at(index);
}

const Person& AddressManager::GetPerson(size_t index) {
    return mPersons.at(index);
}

size_t AddressManager::GetAddressCount() const {
    return mAddresses.size();
}

size_t AddressManager::GetPersonCount() const {
    return mPersons.size();
}
