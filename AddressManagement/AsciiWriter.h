//
// Created by stiangglanda on 2026-10-19.
//

#ifndef ASCIIWRITER_H
#define ASCIIWRITER_H
#include "Writer.h"


class AsciiWriter : public Writer {
public:
    void WriteHeader(std::ofstream& out) override;
    void WriteFooter(std::ofstream& out) override;

};

#endif
