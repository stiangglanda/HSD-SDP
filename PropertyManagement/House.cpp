/// \file House.cpp
/// \author Julian Rieger

#include "House.h"
#include <stdexcept>
#include <iostream>

House::House(const Address &address, const std::vector<Floor>& floors) :
	mAddress(address),
	mFloors(floors)
{
	if (mFloors.empty())
	{
		throw std::invalid_argument("Invalid vector: Cannot add empty floor vector to object house.");
	}
	if (mAddress.GetZip().empty() || mAddress.GetStreet().empty())
	{
		throw std::invalid_argument("Invalid Address: Cannot create house without ZIP or Street.");
	}
}

Address House::GetAddress() const
{
	return mAddress;
}

size_t House::GetFloorCount() const
{
	return mFloors.size();
}

void House::Print() const
{
	for (const auto& floor : mFloors)
	{
		std::cout << "House: ";
		mAddress.Print();
		std::cout << ", " << mFloors.size() << " floors" << std::endl;
		floor.Print();
	}

}