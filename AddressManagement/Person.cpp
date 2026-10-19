#include "Person.h"

Person::Person(std::string firstName, std::string lastName, size_t addressID)
    : mFirstName(firstName),
      mLastName(lastName),
      mAddressID(addressID) {
}

std::string Person::GetFirstName() const {
    return mFirstName;
}

std::string Person::GetLastName() const {
    return mLastName;
}

size_t Person::GetAddressID() const {
    return mAddressID;
}
