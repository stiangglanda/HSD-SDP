#ifndef ADDRESS_H
#define ADDRESS_H
#include <cstddef>
#include <string>
#include "Object.h"

/// @author Julian Rieger
/// @date 21.10.2026
/// @brief Stores a postal address (street, house number, zip code, city).
///
/// The class is a simple value class. All data is set in the constructor
/// and can only be read afterwards, so an address never changes.
class Address : public Object {
public:
    /// @brief Creates an address.
    /// @param[in] street is the name of the street.
    /// @param[in] number is the house number.
    /// @param[in] zip is the zip code.
    /// @param[in] city is the name of the city.
    Address(const std::string& street, std::size_t number, std::size_t zip, const std::string& city);

    /// @brief Access function for the street.
    /// @returns a constant reference to the name of the street.
    const std::string& GetStreet() const;

    /// @brief Access function for the house number.
    /// @returns the house number.
    std::size_t GetNumber() const;

    /// @brief Access function for the zip code.
    /// @returns the zip code.
    std::size_t GetZip() const;

    /// @brief Access function for the city.
    /// @returns a constant reference to the name of the city.
    const std::string& GetCity() const;

private:
    /// @brief Name of the street.
    std::string mStreet;
    /// @brief House number.
    std::size_t mNumber;
    /// @brief Zip code.
    std::size_t mZip;
    /// @brief Name of the city.
    std::string mCity;
};

#endif // ADDRESS_H