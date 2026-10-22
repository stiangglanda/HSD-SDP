#ifndef ADDRESSREADER_H
#define ADDRESSREADER_H

#include "Reader.h"
#include <string>

/// @author Julian Rieger
/// @date 21.10.2026
/// @brief Reads addresses from a file.
///
/// Every data line has the format "street number zip city". The position
/// of the address in the file is the index that the persons refer to.
class AddressReader : public Reader
{
protected:
	/// @brief Parses a line of an address file and adds the address to the manager.
	/// @param[in] line is the line to parse.
	/// @param[in,out] man is the manager that stores the address.
	/// @throws std::runtime_error if the line is not "street number zip city".
	void ParseLine(const std::string& line, IWriteOnlyAddressManager& man) const override;
};

#endif //ADDRESSREADER_H