#include "AsciiWriter.h"
#include <ostream>

void AsciiWriter::WriteHeader(std::ofstream &out) {
    out << "Adressen mit zugeordneten Personen" << std::endl;
    out << "==================\n\n";
}

void AsciiWriter::WriteFooter(std::ofstream &out) {
    out << "\n==================\n";
}

void AsciiWriter::WriteAddress(std::ofstream &out, const Address &address) {
    out << "Adresse: " << address.GetStreet() << ", " << address.GetCity() << std::endl;
}

void AsciiWriter::WritePerson(std::ofstream &out, const Person &person) {
    out << "  Person: " << person.GetFirstName() << " " << person.GetLastName() << std::endl;
}
