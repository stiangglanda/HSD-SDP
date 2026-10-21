#ifndef WRITER_H
#define WRITER_H
#include <ostream>
#include <string>
#include "Address.h"
#include "Person.h"
#include "Object.h"

class AddressManager;

/// @author Leander Kieweg
/// @date 19.10.2026
/// @brief Abstract base class for all writers.
///
/// The class uses the design pattern Template Method. The method Write
/// defines the fixed order of the output. The derived classes only
/// implement the steps and so decide about the file format.
class Writer : public Object
{
public:
   /// @brief Virtual destructor, because writers are used by pointer.
   virtual ~Writer() = default;

   /// @brief Writes all addresses with their persons to a file.
   ///
   /// This is the template method. The order is: header, then for each
   /// address the address, its persons and the end of the address,
   /// and at last the footer.
   /// @param[in] path is the path of the file to write.
   /// @param[in] man is the manager that holds the data.
   /// @throws std::out_of_range if a person refers to an address that does not exist.
   /// @throws std::runtime_error if the file cannot be written.
   void Write(const std::string& path, const AddressManager& man) const;

protected:
   /// @brief Protected default constructor that makes the class abstract.
   Writer() = default;

   /// @brief Writes the beginning of the file.
   /// @param[in] out is the stream to write to.
   virtual void WriteHeader(std::ostream& out) const = 0;

   /// @brief Writes one address.
   /// @param[in] out is the stream to write to.
   /// @param[in] address is the address to write.
   virtual void WriteAddress(std::ostream& out, const Address& address) const = 0;

   /// @brief Writes one person of the current address.
   /// @param[in] out is the stream to write to.
   /// @param[in] person is the person to write.
   virtual void WritePerson(std::ostream& out, const Person& person) const = 0;

   /// @brief Writes the end of the current address block.
   /// @param[in] out is the stream to write to.
   virtual void WriteAddressEnd(std::ostream& out) const = 0;

   /// @brief Writes the end of the file.
   ///
   /// The default writes nothing and can be overridden in derived classes.
   /// @param[in] out is the stream to write to.
   virtual void WriteFooter(std::ostream& out) const {}
};

#endif //WRITER_H