#ifndef PERSON_H
#define PERSON_H
#include <cstddef>
#include <string>
#include "Object.h"

/// @author Julian Rieger
/// @date 21.10.2026
/// @brief Stores a person with its name and a link to its address.
///
/// The link is the index of the address in the AddressManager. The person
/// does not know the address itself, so persons and addresses can be read
/// from files in any order.
class Person : public Object
{
public:
    /// @brief Creates a person.
    /// @param[in] firstName is the first name of the person.
    /// @param[in] lastName is the last name of the person.
    /// @param[in] addressID is the index of the address of the person.
    Person(const std::string& firstName, const std::string& lastName, std::size_t addressID);

    /// @brief Access function for the first name.
    /// @returns a constant reference to the first name.
    const std::string& GetFirstName() const;

    /// @brief Access function for the last name.
    /// @returns a constant reference to the last name.
    const std::string& GetLastName() const;

    /// @brief Access function for the address index.
    /// @returns the index of the address of this person.
    std::size_t GetAddressID() const;

private:
    /// @brief First name of the person.
    std::string mFirstName;
    /// @brief Last name of the person.
    std::string mLastName;
    /// @brief Index of the address in the AddressManager.
    std::size_t mAddressID;
};

#endif // PERSON_H