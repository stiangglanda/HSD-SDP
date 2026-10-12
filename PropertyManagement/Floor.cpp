/// \file Floor.cpp
/// \author Leander Kieweg

#include "Floor.h"
#include <iostream>
#include <stdexcept>

Floor::Floor(size_t number, const std::vector<Flat>& flats)
    : mNumber(number), mFlats(flats) {
    if (mFlats.empty()) {
        throw std::invalid_argument("Floor needs at least one flat");
    }
}

size_t Floor::GetNumber() const { return mNumber; }

size_t Floor::GetFlatCount() const { return mFlats.size(); }

Flat& Floor::GetFlat(size_t index) { return mFlats.at(index); }

void Floor::Print() const {
    std::cout << "  Floor " << mNumber << "\n";
    for (const Flat& flat : mFlats) {
        flat.Print();
    }
}