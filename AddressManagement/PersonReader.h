#ifndef PERSONREADER_H
#define PERSONREADER_H

#include "AddressManager.h"
#include "Reader.h"
#include <string>

class PersonReader : public Reader
{
public:
	void ParseLine(const std::string& line, AddressManager& man) override;
};

#endif //PERSONREADER_H
