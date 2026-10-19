#ifndef HTMLWRITER_H
#define HTMLWRITER_H
#include "Writer.h"

/// @author Leander Kieweg
/// @date 19.10.2026
/// @brief Writes the addresses with their persons as an HTML page.
class HtmlWriter : public Writer
{
protected:
   /// @brief Writes the HTML head, the title and a horizontal line.
   /// @param[in] out is the stream to write to.
   void WriteHeader(std::ostream& out) const override;

   /// @brief Writes an address in italic and opens a new paragraph.
   /// @param[in] out is the stream to write to.
   /// @param[in] address is the address to write.
   void WriteAddress(std::ostream& out, const Address& address) const override;

   /// @brief Writes the name of a person in normal style.
   /// @param[in] out is the stream to write to.
   /// @param[in] person is the person to write.
   void WritePerson(std::ostream& out, const Person& person) const override;

   /// @brief Closes the paragraph of the current address.
   /// @param[in] out is the stream to write to.
   void WriteAddressEnd(std::ostream& out) const override;

   /// @brief Closes the body and the HTML page.
   /// @param[in] out is the stream to write to.
   void WriteFooter(std::ostream& out) const override;
};

#endif //HTMLWRITER_H