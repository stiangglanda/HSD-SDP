#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person {
public:
    Person(std::string firstName, std::string lastName, size_t addressID);
    std::string getFirstName() const;
    std::string getLastName() const;
    size_t getAddressID() const;

private:
    std::string mFirstName;
    std::string mLastName;
    size_t mAddressID;
};

#endif
