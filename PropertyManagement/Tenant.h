#ifndef TENANT_H
#define TENANT_H

#include <cstddef>
#include <string>

/// \file Tenant.h
/// \author Leander Kieweg

/// \brief A main tenant of a flat.
class Tenant {
public:
    /// \brief Creates a tenant.
    /// \param firstName First name.
    /// \param lastName Last name.
    /// \param birthYear Year of birth.
    Tenant(const std::string& firstName, const std::string& lastName, size_t birthYear);

    /// \brief Gets the first name.
    /// \return The first name.
    const std::string& GetFirstName() const;

    /// \brief Gets the last name.
    /// \return The last name.
    const std::string& GetLastName() const;

    /// \brief Changes the first name.
    /// \param firstName The new first name.
    void SetFirstName(const std::string& firstName);

    /// \brief Changes the last name, for example after a marriage.
    /// \param lastName The new last name.
    void SetLastName(const std::string& lastName);

    /// \brief Gets the year of birth.
    /// \return The year of birth.
    size_t GetBirthYear() const;

    /// \brief Prints the tenant to the console, for example: Hans Huber (1950).
    ///        No line break at the end.
    void Print() const;

private:
    std::string mFirstName;
    std::string mLastName;
    size_t mBirthYear;
};

#endif