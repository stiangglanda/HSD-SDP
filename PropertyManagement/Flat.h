#ifndef FLAT_H
#define FLAT_H

#include "Tenant.h"

/// \file Flat.h
/// \author Leander Kieweg

/// \brief A flat. It can have a main tenant or be empty.
///
/// The flat does not own the tenant. It only points to it.
/// The caller must keep the tenant alive as long as the flat uses it.
class Flat {
public:
    /// \brief Creates a flat.
    /// \param number Door number.
    /// \param area Size in square meters.
    /// \param hasBalcony True if the flat has a balcony.
    /// \param tenant Main tenant. nullptr means the flat is empty.
    Flat(size_t number, float area, bool hasBalcony, const Tenant* tenant = nullptr);

    /// \brief Gets the door number.
    /// \return The door number.
    size_t GetNumber() const;

    /// \brief Gets the size.
    /// \return The size in square meters.
    float GetArea() const;

    /// \brief Tells if the flat has a balcony.
    /// \return True if there is a balcony.
    bool HasBalcony() const;

    /// \brief Gets the main tenant.
    /// \return Pointer to the tenant, or nullptr if the flat is empty.
    const Tenant* GetTenant() const;

    /// \brief Changes the main tenant.
    /// \param tenant The new tenant. nullptr makes the flat empty.
    void SetTenant(const Tenant* tenant);

    /// \brief Prints the flat as one line with 4 spaces indent.
    ///        An empty flat shows "vacant" instead of a tenant.
    void Print() const;

private:
    size_t mNumber;
    float mArea;
    bool mHasBalcony;
    const Tenant* mTenant;
};

#endif