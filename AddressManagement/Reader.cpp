
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

static const std::string cFileErr{ "Error in AddressReader: Could not open file." };


void Reader::SkipHeader()
{

}

void Reader::Read(std::string& path, AddressManager& man)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error(cFileErr);
    }
    std::string line{""};
    while (std::getline(file, line))
    {
        ParseLine(line, man);
    }
    
}

void Reader::ParseLine(const std::string& line, AddressManager& man)
{
    if (line.empty()) return; // Skip empty lines
    if (line[0] == '#') return; // Skip Header
    
}


