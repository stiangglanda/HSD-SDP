/// \file Flat.cpp
/// \author Leander Kieweg

#include "Flat.h"
#include <iostream>

Flat::Flat(size_t number, float area, bool hasBalcony, const Tenant* tenant)
    : mNumber(number), mArea(area), mHasBalcony(hasBalcony), mTenant(tenant) {}

size_t Flat::GetNumber() const { return mNumber; }

float Flat::GetArea() const { return mArea; }

bool Flat::HasBalcony() const { return mHasBalcony; }

const Tenant* Flat::GetTenant() const { return mTenant; }

void Flat::SetTenant(const Tenant* tenant) { mTenant = tenant; }

void Flat::Print() const {
    std::cout << "    Flat " << mNumber << ", " << mArea << "qm, "
              << (mHasBalcony ? "with balcony" : "no balcony") << ": ";
    if (mTenant != nullptr) {
        mTenant->Print();
    } else {
        std::cout << "vacant";
    }
}