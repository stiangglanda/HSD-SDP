#include "Person.h"

Person::Person(const std::string& firstName, const std::string& lastName, std::size_t addressID)
    : mFirstName(firstName),
    mLastName(lastName),
    mAddressID(addressID) {
}

const std::string& Person::GetFirstName() const {
    return mFirstName;
}

const std::string& Person::GetLastName() const {
    return mLastName;
}

std::size_t Person::GetAddressID() const {
    return mAddressID;
}