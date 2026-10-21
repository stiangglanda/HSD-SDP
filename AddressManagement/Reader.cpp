
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

static const std::string cFileErr{ "Error in AddressReader: Could not open file." };

void Reader::Read(const std::string& path, AddressManager& man) const
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error(cFileErr);
    }

    std::string line{""};
    while (std::getline(file, line))
    {
        if (line[0] == '#')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    ParseLine(line, man);
    while (std::getline(file, line))
    {
        ParseLine(line, man);
    }
    
}


