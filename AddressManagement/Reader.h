

#ifndef ADDRESSMANAGEMENT_READER_H
#define ADDRESSMANAGEMENT_READER_H

#include "AddressManager.h"
#include <string>

class Reader {
public:
	void Read(std::string& path, AddressManager& man);
	void ParseLine(const std::string& line, AddressManager& man);
protected:
	void SkipHeader();
private:
};


#endif //ADDRESSMANAGEMENT_READER_H
