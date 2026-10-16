/// \file PropertyManagement.cpp
/// \author Julian Rieger

#include "PropertyManagement.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

void PropertyManagement::Print() const
{
    for (const auto& house : mHouses)
    {
        house.Print();
        std::cout << "\n";
    }
}

void PropertyManagement::AddHouse(const House& house)
{
    auto it = std::find_if(mHouses.cbegin(), mHouses.cend(),
        [&house](const House& h) {
            return h.GetAddress() == house.GetAddress();
        });

    if (it != mHouses.cend())
    {
        throw std::invalid_argument("House with this address already exists.");
    }

    mHouses.push_back(house);
}

void PropertyManagement::RemoveHouse(const Address& address)
{
    auto it = std::find_if(mHouses.begin(), mHouses.end(),
        [&address](const House& h) {
            return h.GetAddress() == address;
        });

    if (it == mHouses.end())
    {
        throw std::out_of_range("House with this address not found.");
    }

    mHouses.erase(it);
}

size_t PropertyManagement::GetHouseCount() const
{
    return mHouses.size();
}