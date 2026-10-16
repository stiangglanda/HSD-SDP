#ifndef HOUSE_H
#define HOUSE_H

/// \file House.h
/// \author Julian Rieger

#include "Floor.h"
#include "Address.h"

/// \brief Represents a house uniquely identified by an address with a fixed set of floors.
class House
{
public:
	/// \brief Creates a house.
	/// \param address The postal address of the house.
	/// \param floors Vector containing the floors of this house. Must not be empty.
	/// \throws std::invalid_argument If the floors vector is empty.
	House(const Address& address, const std::vector<Floor>& floors);

	/// \brief Prints the house and all its floors and flats to std::cout.
	void Print() const;

	/// \brief Gets the address of the house.
	/// \return Const reference to the address.
	const Address& GetAddress() const;

	/// \brief Gets the total number of floors.
	/// \return The number of floors in the house.
	size_t GetFloorCount() const;

private:
	std::vector<Floor> mFloors;
	Address mAddress;
};

#endif