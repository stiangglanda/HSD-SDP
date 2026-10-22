#ifndef ADDRESSMANAGER_H
#define ADDRESSMANAGER_H
#include <cstddef>
#include <string>
#include <vector>
#include "Person.h"
#include "Address.h"
#include "AddPersonAddress.h"
#include "GetPersonAddress.h"

class Reader;
class Writer;

/// @author Leander Kieweg
/// @date 19.10.2026
/// @brief Manages addresses and persons and links them to each other.
///
/// A person refers to its address by an index. The manager reads its data
/// with a Reader and writes it with a Writer. Both are passed as pointers,
/// so the caller decides which file format is used.
class AddressManager : public AddPersonAddress, public GetPersonAddress, public Object
{
public:
   /// @brief Reads a file with the given reader.
   /// @param[in] path is the path of the file to read.
   /// @param[in] rdr is the reader that knows the file format.
   /// @throws std::invalid_argument if rdr is a null pointer.
   void ReadFile(const std::string& path, const Reader* rdr);

   /// @brief Writes all addresses with their persons to a file.
   /// @param[in] path is the path of the file to write.
   /// @param[in] wrt is the writer that knows the file format.
   /// @throws std::invalid_argument if wrt is a null pointer.
   void WriteAddresses(const std::string& path, const Writer* wrt) const;

   /// @brief Access function for an address.
   /// @param[in] index is the position of the address.
   /// @returns a constant reference to the address.
   /// @throws std::out_of_range if the index does not exist.
   const Address& GetAddress(size_t index) const;

   /// @brief Access function for a person.
   /// @param[in] index is the position of the person.
   /// @returns a constant reference to the person.
   /// @throws std::out_of_range if the index does not exist.
   const Person& GetPerson(size_t index) const;

   /// @brief Access function for the number of addresses.
   /// @returns the number of stored addresses.
   size_t GetAddressCount() const;

   /// @brief Access function for the number of persons.
   /// @returns the number of stored persons.
   size_t GetPersonCount() const;

private:
   /// Only the readers are allowed to add new entries.
   friend class PersonReader;
   friend class AddressReader;

   /// @brief Adds a person to the manager.
   /// @param[in] person is the person to store.
   void AddPerson(const Person& person);

   /// @brief Adds an address to the manager.
   /// @param[in] address is the address to store.
   void AddAddress(const Address& address);

   /// @brief All persons in the order they were read.
   std::vector<Person> mPersons;

   /// @brief All addresses. The position is the index used by the persons.
   std::vector<Address> mAddresses;
};

#endif