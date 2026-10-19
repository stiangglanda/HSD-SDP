#include "AsciiWriter.h"
#include <ostream>

void AsciiWriter::WriteHeader(std::ofstream &out) {
    out << "Adressen mit zugeordneten Personen" << std::endl;
    out << "==================\n\n";
}

void AsciiWriter::WriteFooter(std::ofstream &out) {
}
