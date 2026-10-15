#ifndef PROPERTYMANAGEMENT_H
#define PROPERTYMANAGEMENT_H

#include "House.h"


/// \file PropertyManagement.h
/// \author Julian Rieger

/// \brief Object containing existing houses and underlying objects.
///
/// PropertyManagement contains vector of all houses.
class PropertyManagement
{
public:

/// \brief Object containing existing houses and underlying objects.
	void Print() const;

/// \brief Object containing existing houses and underlying objects.
	void AddHouse(const House& house);

private:
	std::vector<House> mHouses;
};
#endif //PROPERTYMANAGEMENT_H