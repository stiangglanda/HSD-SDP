#ifndef ADDPERSONADDRESS_H
#define ADDPERSONADDRESS_H

#include "Person.h"
#include "Address.h"

class AddPersonAddress
{
public:

	/// @brief Adds a person to the manager.
	/// @param[in] person is the person to store.
	virtual void AddPerson(const Person& person) = 0;

	/// @brief Adds an address to the manager.
	/// @param[in] address is the address to store.
	virtual void AddAddress(const Address& address) = 0;
};

#endif //ADDPERSONADDRESS_H