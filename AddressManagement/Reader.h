

#ifndef ADDRESSMANAGEMENT_READER_H
#define ADDRESSMANAGEMENT_READER_H

#include "AddressManager.h"
#include <string>

class Reader {
public:
	void Read(std::string& path, AddressManager& man);
	virtual void ParseLine(const std::string& line, AddressManager& man);
protected:
	Reader() = default;
private:
	void SkipHeader(std::ifstream& file);
};


#endif //ADDRESSMANAGEMENT_READER_H
