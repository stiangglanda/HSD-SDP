#ifndef PERSONREADER_H
#define PERSONREADER_H

#include "AddressManager.h"
#include "Reader.h"
#include <string>

/// @author Julian Rieger
/// @date 21.10.2026
/// @brief Reads persons from a file.
///
/// Every data line has the format "firstname lastname addressIndex".
/// The parsed person is added to the AddressManager.
class PersonReader : public Reader
{
protected:
	/// @brief Parses a line of a person file and adds the person to the manager.
	/// @param[in] line is the line to parse.
	/// @param[in,out] man is the manager that stores the person.
	/// @throws std::runtime_error if the line is not "firstname lastname index".
	void ParseLine(const std::string& line, AddressManager& man) const override;
};

#endif //PERSONREADER_H