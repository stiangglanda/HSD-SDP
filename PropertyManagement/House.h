#ifndef HOUSE_H
#define HOUSE_H

#include "Floor.h"
#include "Address.h"

/// \file House.h
/// \author Julian Rieger

/// \brief Object of house containing various Floors
///
/// 
class House
{
public:
/// \brief Creates a house.
/// \param address Uses object address to clarify Streetname, ZIP and City
/// \param floors Vector containing all existing floors.
/// \throws std::invalid_argument If floors is empty or address is faulty.
	House(const Address &address, const std::vector<Floor>& floors);

/// \brief Prints a house including its floors and flats.
	void Print() const;

/// \brief Returns member mAddress.
	Address GetAddress() const;

/// \brief Returns number of floors
	size_t GetFloorCount() const;
private:
	std::vector<Floor> mFloors;
	Address mAddress;
};

#endif