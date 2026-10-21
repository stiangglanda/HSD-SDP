#include "AddressReader.h"
#include <sstream>

static const std::string cErrStream{ "Error in AddressReader: bad stream" };

void AddressReader::ParseLine(const std::string& line, AddressManager& man) const
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
		throw std::runtime_error(cErrStream);
	}
}

