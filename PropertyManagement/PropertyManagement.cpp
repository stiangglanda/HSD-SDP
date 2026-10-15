/// \file PropertyManagement.cpp
/// \author Julian Rieger

#include "PropertyManagement.h"
#include <iostream>

void PropertyManagement::Print()
{
	for (const auto &house : mHouses)
	{
		house.Print();
		std::cout << std::endl;
	}
}

void PropertyManagement::AddHouse(const House& house)
{
	mHouses.push_back(house);
}
