#ifndef HTMLWRITER_H
#define HTMLWRITER_H
#include "Writer.h"

class HtmlWriter : public Writer {

    public:
    void WriteHeader(std::ofstream& out) override;
    void WriteFooter(std::ofstream& out) override;
    void WriteAddress(std::ofstream & out, const Address& address) override;
    void WritePerson(std::ofstream & out, const Person& person) override;
};

#endif
