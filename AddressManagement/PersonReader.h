#ifndef PERSONREADER_H
#define PERSONREADER_H

#include "AddressManager.h"
#include <string>

class PersonReader
{
public:
	void ParseLine(const std::string& line, AddressManager& man);
private:
};

#endif //PERSONREADER_H
