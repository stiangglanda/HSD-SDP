/// \file Tenant.cpp
/// \author Leander Kieweg

#include "Tenant.h"
#include <iostream>

Tenant::Tenant(const std::string& firstName, const std::string& lastName, size_t birthYear)
    : mFirstName(firstName), mLastName(lastName), mBirthYear(birthYear) {}

const std::string& Tenant::GetFirstName() const { return mFirstName; }

const std::string& Tenant::GetLastName() const { return mLastName; }

void Tenant::SetFirstName(const std::string& firstName) { mFirstName = firstName; }

void Tenant::SetLastName(const std::string& lastName) { mLastName = lastName; }

size_t Tenant::GetBirthYear() const { return mBirthYear; }

void Tenant::Print() const {
    std::cout << mFirstName << " " << mLastName << " (" << mBirthYear << ")";
}