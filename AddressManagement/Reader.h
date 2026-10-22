#ifndef ADDRESSMANAGEMENT_READER_H
#define ADDRESSMANAGEMENT_READER_H

#include <string>
#include "Object.h"
#include "AddPersonAddress.h"

class AddressManager;

/// @author Julian Rieger
/// @date 21.10.2026
/// @brief Abstract base class for all readers.
///
/// The class uses the design pattern Template Method. The method Read
/// defines the fixed procedure of reading a file: open the file, skip the
/// header and empty lines and pass every data line to ParseLine. The derived
/// classes only implement ParseLine and so decide about the line format.
class Reader : public Object
{
public:
	/// @brief Virtual destructor, because readers are used by pointer.
	virtual ~Reader() = default;

	/// @brief Reads a file and stores its content in the manager.
	///
	/// This is the template method. Lines that start with '#' (header) and
	/// lines that contain only white space are skipped. Every other line is
	/// passed to ParseLine.
	/// @param[in] path is the path of the file to read.
	/// @param[in,out] man is the manager that stores the parsed data.
	/// @throws std::runtime_error if the file cannot be opened or read, or
	///         if a line has a wrong format.
	void Read(const std::string& path, AddPersonAddress& man) const;

protected:
	/// @brief Protected default constructor that makes the class abstract.
	Reader() = default;

	/// @brief Parses one data line and adds the result to the manager.
	/// @param[in] line is the line to parse (without line break).
	/// @param[in,out] man is the manager that stores the parsed data.
	/// @throws std::runtime_error if the line has a wrong format.
	virtual void ParseLine(const std::string& line, AddPersonAddress& man) const = 0;
};

#endif //ADDRESSMANAGEMENT_READER_H