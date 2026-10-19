#include "AddressManager.h"
#include <stdexcept>
#include "Reader.h"
#include "Writer.h"

void AddressManager::ReadFile(const std::string& path, const Reader* rdr)
{
    if (rdr == nullptr)
        throw std::invalid_argument("Reader is a null pointer");
    //rdr->Read(path, *this);
}

void AddressManager::WriteAddresses(const std::string& path, const Writer* wrt) const
{
    if (wrt == nullptr)
        throw std::invalid_argument("Writer is a null pointer");
    wrt->Write(path, *this);
}

void AddressManager::AddPerson(const Person& person)
{
    mPersons.push_back(person);
}

void AddressManager::AddAddress(const Address& address)
{
    mAddresses.push_back(address);
}

const Address& AddressManager::GetAddress(size_t index) const
{
    return mAddresses.at(index);   // throws std::out_of_range for a wrong index
}

const Person& AddressManager::GetPerson(size_t index) const
{
    return mPersons.at(index);
}

size_t AddressManager::GetAddressCount() const
{
    return mAddresses.size();
}

size_t AddressManager::GetPersonCount() const
{
    return mPersons.size();
}