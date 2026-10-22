#include "Writer.h"
#include <fstream>
#include <stdexcept>
#include "AddressManager.h"

void Writer::Write(const std::string& path, const GetPersonAddress& man) const
{
    // Check first, so that no half written file is created.
    for (size_t p = 0; p < man.GetPersonCount(); ++p) {
        if (man.GetPerson(p).GetAddressID() >= man.GetAddressCount())
            throw std::out_of_range("Person " + std::to_string(p) +
                                    " refers to an address that does not exist");
    }

    std::ofstream out(path);
    if (!out)
        throw std::runtime_error("File cannot be written: " + path);

    WriteHeader(out);

    for (size_t a = 0; a < man.GetAddressCount(); ++a) {
        WriteAddress(out, man.GetAddress(a));

        // Write all persons that refer to this address.
        for (size_t p = 0; p < man.GetPersonCount(); ++p) {
            const Person& person = man.GetPerson(p);
            if (person.GetAddressID() == a)
                WritePerson(out, person);
        }
        WriteAddressEnd(out);
    }

    WriteFooter(out);

    if (!out)
        throw std::runtime_error("Error while writing: " + path);
}