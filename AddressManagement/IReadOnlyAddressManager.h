#ifndef GETPERSONADDRESS_H
#define GETPERSONADDRESS_H

class IReadOnlyAddressManager
{
public: 
	/// @brief Access function for an address.
	/// @param[in] index is the position of the address.
	/// @returns a constant reference to the address.
	/// @throws std::out_of_range if the index does not exist.
	virtual const Address& GetAddress(size_t index) const = 0;

	/// @brief Access function for a person.
	/// @param[in] index is the position of the person.
	/// @returns a constant reference to the person.
	/// @throws std::out_of_range if the index does not exist.
	virtual const Person& GetPerson(size_t index) const = 0;

	/// @brief Access function for the number of addresses.
	/// @returns the number of stored addresses.
	virtual size_t GetAddressCount() const = 0;

	/// @brief Access function for the number of persons.
	/// @returns the number of stored persons.
	virtual size_t GetPersonCount() const = 0;

};

#endif