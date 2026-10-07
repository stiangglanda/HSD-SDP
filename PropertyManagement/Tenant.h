#ifndef TENANT_H
#define TENANT_H

#include <string>

class Tenant
{
public:

	Tenant(std::string first, std::string last, size_t year) :
		mFirstName(first),
		mLastName(last),
		mBirthYear(year) {}

	std::string GetFirstName();
	std::string GetLastName();
	size_t GetBirthYear();

private:

	std::string mFirstName;
	std::string mLastName;
	size_t mBirthYear;
};


#endif //TENANT_H