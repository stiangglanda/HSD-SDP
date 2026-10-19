#ifndef ASCIIWRITER_H
#define ASCIIWRITER_H
#include "Writer.h"

/// @author Leander Kieweg
/// @date 19.10.2026
/// @brief Writes the addresses with their persons as plain text.
class AsciiWriter : public Writer
{
protected:
   /// @brief Writes the title and a line below it.
   /// @param[in] out is the stream to write to.
   void WriteHeader(std::ostream& out) const override;

   /// @brief Writes the zip code and city, then the street and number.
   /// @param[in] out is the stream to write to.
   /// @param[in] address is the address to write.
   void WriteAddress(std::ostream& out, const Address& address) const override;

   /// @brief Writes the name of a person, indented by four spaces.
   /// @param[in] out is the stream to write to.
   /// @param[in] person is the person to write.
   void WritePerson(std::ostream& out, const Person& person) const override;

   /// @brief Writes an empty line between two addresses.
   /// @param[in] out is the stream to write to.
   void WriteAddressEnd(std::ostream& out) const override;
};

#endif //ASCIIWRITER_H