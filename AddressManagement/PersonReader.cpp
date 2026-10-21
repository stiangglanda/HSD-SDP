#include "PersonReader.h"
#include <sstream>

static const std::string cErrStream{ "Error in PersonReader: bad stream" };

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
		throw std::runtime_error(cErrStream);
	}
}
