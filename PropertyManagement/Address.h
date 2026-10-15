#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

/// \file Address.h
/// \author Julian Rieger

/// \brief Address contains of Street Name and Zipcode
///
/// Zipcode and Address are saved as std::string
class Address
{
public:
	/// \brief Creates address.
	/// \param zip The Zipcode of the address
	/// \param street The sreet of the address
	/// \throws std::invalid_argument if either argument is empty.
	Address(std::string street, std::string zip, std::string city);

	/// \brief Returns member mZip.
	std::string GetZip();

	/// \brief Returns member mStreet.
	std::string GetStreet();

	/// \brief Returns member mCity.
	std::string GetCity();

	///	\brief Prints Address formated on console.
	void Print() const;
private:
	std::string mZip;
	std::string mStreet;
	std::string mCity;
};

#endif