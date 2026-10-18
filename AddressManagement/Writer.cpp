//
// Created by stiangglanda on 2026-10-18.
//

#include "Writer.h"

#include <fstream>
#include <stdexcept>

#include "AddressManager.h"

void Writer::Write(const std::string& path, AddressManager& man)
{
    std::ofstream out(path);
    if (!out)
        throw std::runtime_error("Datei nicht beschreibbar: " + path);

    WriteHeader(out);

    // for (size_t a = 0; a < man.GetAddressCount(); ++a)
    // {
    //     WriteAddress(out, man.GetAddress(a));
    //
    //     // alle Personen suchen, die auf diese Adresse zeigen
    //     for (size_t p = 0; p < man.GetPersonCount(); ++p)
    //     {
    //         if (man.GetPerson(p).GetAddressID() == a)
    //             WritePerson(out, man.GetPerson(p));
    //     }
    // }
    //
    // WriteFooter(out);
}
