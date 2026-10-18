#include "Person.h"

Person::Person(std::string firstName, std::string lastName, size_t addressID)
    : mFirstName(firstName),
      mLastName(lastName),
      mAddressID(addressID) {
}

std::string Person::getFirstName() const {
    return mFirstName;
}

std::string Person::getLastName() const {
    return mLastName;
}

size_t Person::getAddressID() const {
    return mAddressID;
}
