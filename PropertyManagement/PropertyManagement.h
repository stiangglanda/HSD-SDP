#ifndef PROPERTYMANAGEMENT_H
#define PROPERTYMANAGEMENT_H

#include "House.h"
#include <vector>

/// \file PropertyManagement.h
/// \author Julian Rieger

/// \brief Object containing existing houses and managing them.
class PropertyManagement
{
public:
    /// \brief Prints all houses.
    void Print() const;

    /// \brief Adds a house if its address is unique.
    /// \param house The house to add.
    /// \throws std::invalid_argument If a house with this address already exists.
    void AddHouse(const House& house);

    /// \brief Removes a house by its address.
    /// \param address Address of the house to remove.
    /// \throws std::out_of_range If no house with this address is found.
    void RemoveHouse(const Address& address);

    /// \brief Returns the number of managed houses.
    /// \return Number of houses.
    size_t GetHouseCount() const;

private:
    std::vector<House> mHouses;
};

#endif