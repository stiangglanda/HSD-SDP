/// \file Address.cpp
/// \author Julian Rieger

#include "Address.h"
#include <stdexcept>
#include <iostream>

Address::Address(const std::string& street, const std::string& zip, const std::string& city) :
	mZip(zip),
	mStreet(street),
	mCity(city)
{
	if (zip.empty() || street.empty() || city.empty())
	{
		throw std::invalid_argument("Invalid argument: Zip code, city or street name is empty.");
	}
}

std::string Address::GetZip() const
{
	return mZip;
}

std::string Address::GetStreet() const
{
	return mStreet;
}

std::string Address::GetCity() const
{
	return mCity;
}

void Address::Print() const
{
	std::cout << mStreet << ", " << mZip << " " << mCity;
}