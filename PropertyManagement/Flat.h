#ifndef FLAT_H
#define FLAT_H

#include "Tenant.h"

class Flat
{
public:

	void ChangeTenant(Tenant& other);
	bool GetBalcony();
	size_t GetNumber();
	float GetSpace();
	Tenant& GetTenant();

private:

	bool mBalcony;
	size_t mNumber;
	float mSpace;
	Tenant* mTenant;
};

#endif //FLAT_H