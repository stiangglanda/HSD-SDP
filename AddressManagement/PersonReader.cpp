#include "PersonReader.h"
#include <sstream>
#include <stdexcept>

void PersonReader::ParseLine(const std::string& line, AddressManager& man) const
{
	std::string firstname;
	std::string lastname;
	std::size_t number;

	std::stringstream sstream(line);

	if (sstream >> firstname >> lastname >> number)
	{
		Person p{ firstname, lastname, number };
		man.AddPerson(p);
	}
	else
	{
		throw std::runtime_error("Error in PersonReader: bad stream");
	}
}