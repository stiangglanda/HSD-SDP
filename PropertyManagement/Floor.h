#ifndef FLOOR_H
#define FLOOR_H

#include "Flat.h"
#include <vector>

/// \file Floor.h
/// \author Leander Kieweg

/// \brief A floor of a house with a fixed number of flats.
///
/// The flats are given at creation. Flats cannot be added or removed later.
class Floor {
public:
    /// \brief Creates a floor.
    /// \param number Floor number. The ground floor is 0.
    /// \param flats The flats on this floor. Must not be empty.
    /// \throws std::invalid_argument If flats is empty.
    Floor(size_t number, const std::vector<Flat>& flats);

    /// \brief Gets the floor number.
    /// \return The floor number.
    size_t GetNumber() const;

    /// \brief Gets the number of flats.
    /// \return The number of flats on this floor.
    size_t GetFlatCount() const;

    /// \brief Gets a flat by its door number so its tenant can be changed.
    /// \param number Door number of the flat.
    /// \return Reference to the flat.
    /// \throws std::out_of_range If no flat with this number exists.
    Flat& GetFlat(size_t number);

    /// \brief Gets a flat by its door number for read-only access.
    /// \param number Door number of the flat.
    /// \return Const reference to the flat.
    /// \throws std::out_of_range If no flat with this number exists.
    const Flat& GetFlat(size_t number) const;

    /// \brief Prints the floor with 2 spaces indent, followed by its flats.
    void Print() const;

private:
    size_t mNumber;
    std::vector<Flat> mFlats;
};

#endif