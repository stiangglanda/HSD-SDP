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
}

const Address& House::GetAddress() const
{
	return mAddress;
}

size_t House::GetFloorCount() const
{
	return mFloors.size();
}

void House::Print() const
{
	std::cout << "House: ";
	mAddress.Print();
	std::cout << ", " << mFloors.size() << " floors\n";
	for (const auto& floor : mFloors)
	{
		floor.Print();
	}
}