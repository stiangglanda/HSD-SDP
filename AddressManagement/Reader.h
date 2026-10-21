

#ifndef ADDRESSMANAGEMENT_READER_H
#define ADDRESSMANAGEMENT_READER_H

#include "AddressManager.h"
#include "Object.h"
#include <string>

class Reader : public Object
{
public:
	void Read(const std::string& path, AddressManager& man) const;
	virtual void ParseLine(const std::string& line, AddressManager& man) const = 0;
protected:
	Reader() = default;
};


#endif //ADDRESSMANAGEMENT_READER_H
