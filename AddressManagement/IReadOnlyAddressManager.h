#ifndef IREADONLYADDRESSMANAGER_H
#define IREADONLYADDRESSMANAGER_H

#include <cstddef>
#include "Address.h"
#include "Person.h"

/// @author Leander Kieweg
/// @date 21.10.2026
/// @brief Interface for read-only access to persons and addresses.
///
/// Follows the Interface Segregation Principle (ISP). It provides only 
/// inspection methods required by Writers to format and export data, 
/// preventing unintended modifications.
class IReadOnlyAddressManager
{
public:
	/// @brief Virtual default destructor for safe polymorphic deletion.
    virtual ~IReadOnlyAddressManager() = default;

    /// @brief Access function for an address.
    /// @param[in] index is the position of the address.
    /// @returns a constant reference to the address.
    /// @throws std::out_of_range if the index does not exist.
    virtual const Address& GetAddress(std::size_t index) const = 0;

    /// @brief Access function for a person.
    /// @param[in] index is the position of the person.
    /// @returns a constant reference to the person.
    /// @throws std::out_of_range if the index does not exist.
    virtual const Person& GetPerson(std::size_t index) const = 0;

    /// @brief Access function for the number of addresses.
    /// @returns the number of stored addresses.
    virtual std::size_t GetAddressCount() const = 0;

    /// @brief Access function for the number of persons.
    /// @returns the number of stored persons.
    virtual std::size_t GetPersonCount() const = 0;
};

#endif // IREADONLYADDRESSMANAGER_H