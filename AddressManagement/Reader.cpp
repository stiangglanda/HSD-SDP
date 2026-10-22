#include "Reader.h"
#include <fstream>
#include <stdexcept>

void Reader::Read(const std::string& path, AddPersonAddress& man) const
{
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Error in Reader: could not open file '" + path + "'");
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Skip the header (lines starting with '#') and empty lines
        if (!std::isalpha(line[0]) || line[0] == '#')
        {
            continue;
        }
        ParseLine(line, man);
    }

    // getline also stops at a real read error, not only at the end of the file.
    if (file.bad()) {
        throw std::runtime_error("Error in Reader: could not read file '" + path + "'");
    }

    file.close();
}