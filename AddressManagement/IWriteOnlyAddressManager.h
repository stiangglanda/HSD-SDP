#ifndef IWRITEONLYADDRESSMANAGER_H
#define IWRITEONLYADDRESSMANAGER_H

#include "Address.h"
#include "Person.h"

/// @author Leander Kieweg
/// @date 21.10.2026
/// @brief Interface for adding persons and addresses (write-only access).
///
/// Follows the Interface Segregation Principle (ISP). It provides only 
/// mutating methods required by Readers to populate data, without exposing 
/// read access or management functions.
class IWriteOnlyAddressManager
{
public:
    /// @brief Virtual default destructor for safe polymorphic deletion.
    virtual ~IWriteOnlyAddressManager() = default;

    /// @brief Adds a person to the manager.
    /// @param[in] person is the person to store.
    virtual void AddPerson(const Person& person) = 0;

    /// @brief Adds an address to the manager.
    /// @param[in] address is the address to store.
    virtual void AddAddress(const Address& address) = 0;
};

#endif // IWRITEONLYADDRESSMANAGER_H