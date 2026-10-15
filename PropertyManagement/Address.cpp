/// \file Address.cpp
/// \author Julian Rieger

#include "Address.h"
#include <stdexcept>
#include <iostream>

Address::Address(std::string street, std::string zip, std::string city) :
	mZip(zip),
	mStreet(street),
	mCity(city)
{
	if (zip.empty() || street.empty() || city.empty())
	{
		throw std::invalid_argument("Invalid argument: Zip code, city or street name is empty.");
	}
}

std::string Address::GetZip()
{
	return mZip;
}

std::string Address::GetStreet()
{
	return mStreet;
}

std::string Address::GetCity()
{
	return mCity;
}

void Address::Print() const
{
	std::cout << mStreet << " ," << mZip << " " << mCity;
}