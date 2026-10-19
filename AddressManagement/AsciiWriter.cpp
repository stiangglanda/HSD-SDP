#include "AsciiWriter.h"

void AsciiWriter::WriteHeader(std::ostream& out) const
{
    const std::string title = "Adressen mit zugeordneten Personen";
    out << title << '\n'
        << std::string(title.size(), '-') << '\n';   // line as long as the title
}

void AsciiWriter::WriteAddress(std::ostream& out, const Address& address) const
{
    out << address.GetZip() << ' ' << address.GetCity() << '\n'
        << address.GetStreet() << ' ' << address.GetNumber() << '\n';
}

void AsciiWriter::WritePerson(std::ostream& out, const Person& person) const
{
    out << "    " << person.GetFirstName() << ' ' << person.GetLastName() << '\n';
}

void AsciiWriter::WriteAddressEnd(std::ostream& out) const
{
    out << '\n';
}