#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person {
public:
    Person(std::string firstName, std::string lastName, size_t addressID);
    std::string GetFirstName() const;
    std::string GetLastName() const;
    size_t GetAddressID() const;

private:
    std::string mFirstName;
    std::string mLastName;
    size_t mAddressID;
};

#endif
