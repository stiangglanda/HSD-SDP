#ifndef ADDRESSREADER_H
#define ADDRESSREADER_H

#include "AddressManager.h"
#include "Reader.h"
#include <string>

class AddressReader : public Reader
{
public:
	void ParseLine(const std::string& line, AddressManager& man) const override;
};

#endif //ADDRESSREADER_H
