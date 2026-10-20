#ifndef ADDRESSREADER_H
#define ADDRESSREADER_H

#include "AddressManager.h"
#include <string>

class AddressReader
{
public:
	void ParseLine(const std::string& line, AddressManager& man);
private:
};

#endif //ADDRESSREADER_H
