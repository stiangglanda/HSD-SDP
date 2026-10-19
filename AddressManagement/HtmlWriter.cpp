#include "HtmlWriter.h"

void HtmlWriter::WriteHeader(std::ofstream &out) {
    out << "<!DOCTYPE html>" << std::endl;
    out << "<html lang=\"en\">" << std::endl;
    out << "<head>" << std::endl;
    out << "    <meta charset=\"UTF-8\">" << std::endl;
    out << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << std::endl;
    out << "    <title>Address Book</title>" << std::endl;
    out << "</head>" << std::endl;
    out << "<body>" << std::endl;
}

void HtmlWriter::WriteFooter(std::ofstream &out) {
    out << "</body>" << std::endl;
    out << "</html>" << std::endl;
}

void HtmlWriter::WriteAddress(std::ofstream &out, const Address &address) {
    out << "<div class=\"address\">" << std::endl;
    out << "    <h3>" << address.GetStreet() << ", " << address.GetNumber() << "</h3>" << std::endl;
    out << "    <p>" << address.GetCity() << ", " << address.GetZip() << "</p>" << std::endl;
    out << "</div>" << std::endl;
}

void HtmlWriter::WritePerson(std::ofstream &out, const Person &person) {
    out << "<div class=\"person\">" << std::endl;
    out << "    <h3>" << person.GetFirstName() << " " << person.GetLastName() << "</h3>" << std::endl;
    out << "</div>" << std::endl;
}
