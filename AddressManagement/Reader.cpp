
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

static const std::string cFileErr{ "Error in AddressReader: Could not open file." };

void Reader::SkipHeader(std::ifstream& file)
{
    std::string line{ "" };
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
}

void Reader::Read(std::string& path, AddressManager& man)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error(cFileErr);
    }
    SkipHeader(file);

    std::string line{""};
    while (std::getline(file, line))
    {
        ParseLine(line, man);
    }
    
}


