#include "HtmlWriter.h"

void HtmlWriter::WriteHeader(std::ostream& out) const
{
    out << "<!DOCTYPE html>\n"
        << "<html lang=\"de\">\n"
        << "<head>\n"
        << "    <meta charset=\"UTF-8\">\n"
        << "    <title>Adressen mit zugeordneten Personen</title>\n"
        << "</head>\n"
        << "<body>\n"
        << "<h3>Adressen mit zugeordneten Personen</h3>\n"
        << "<hr>\n";
}

void HtmlWriter::WriteAddress(std::ostream& out, const Address& address) const
{
    out << "<p>\n"
        << "<i>" << address.GetZip() << ' ' << address.GetCity() << "<br>\n"
        << address.GetStreet() << ' ' << address.GetNumber() << "</i><br>\n";
}

void HtmlWriter::WritePerson(std::ostream& out, const Person& person) const
{
    out << person.GetFirstName() << ' ' << person.GetLastName() << "<br>\n";
}

void HtmlWriter::WriteAddressEnd(std::ostream& out) const
{
    out << "</p>\n";
}

void HtmlWriter::WriteFooter(std::ostream& out) const
{
    out << "</body>\n"
        << "</html>\n";
}