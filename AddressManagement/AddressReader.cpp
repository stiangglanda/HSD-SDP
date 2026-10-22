#include "AddressReader.h"
#include <sstream>
#include <stdexcept>

void AddressReader::ParseLine(const std::string& line, IWriteOnlyAddressManager& man) const
{
	std::string street;
	std::size_t number;
	std::size_t zip;
	std::string city;

	std::stringstream sstream(line);

	if (sstream >> street >> number >> zip >> city)
	{
		Address a{ street, number, zip, city };
		man.AddAddress(a);
	}
	else
	{
		throw std::runtime_error("Error in AddressReader: bad stream");
	}
}