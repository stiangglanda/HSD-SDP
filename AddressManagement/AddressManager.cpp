#include "AddressManager.h"
#include "Writer.h"

void AddressManager::ReadFile(std::string path, Reader rdr) {
}

void AddressManager::WriteAddresses(std::string path, Writer& wrt) {

}

void AddressManager::AddPerson(const Person& person) {
    mPersons.push_back(person);
}

void AddressManager::AddAddress(const Address& address) {
    mAddresses.push_back(address);
}

void AddressManager::GetAddress(size_t index) {
}

void AddressManager::GetPerson(size_t index) {
}
