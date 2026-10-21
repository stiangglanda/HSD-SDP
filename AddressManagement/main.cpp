/// \file main.cpp
/// \brief Test driver. Runs all tests and prints the results.
/// \author Leander Kieweg, Julian Rieger

#include <iostream>
#include <string>

#include "Address.h"
#include "AddressManager.h"
#include "AsciiWriter.h"
#include "HtmlWriter.h"
#include "Person.h"
#include "PersonReader.h"
#include "AddressReader.h"

/// \brief Helper function to report test outcomes.
void CheckTest(bool condition, const std::string& testName)
{
    if (condition)
    {
        std::cout << "[SUCCESS] " << testName << std::endl;
    }
    else
    {
        std::cerr << "[FAILED]  " << testName << std::endl;
    }
}

void RunTestDriver();

/// \brief Starts the program.
/// \return 0.
int main()
{
    RunTestDriver();

    return 0;
}

void RunTestDriver()
{
    AddressManager man;
    PersonReader pReader;
    AddressReader aReader;
    HtmlWriter hWriter;
    AsciiWriter aWriter;

    const std::string personPath{ "../../../pers.txt" };
    const std::string addressPath{ "../../../adr.txt" };
    const std::string resultPathHtml{ "../../../result.html" };
    const std::string resultPathAscii{ "../../../result.txt" };


    man.ReadFile(personPath, &pReader);
    man.ReadFile(addressPath, &aReader);
    man.WriteAddresses(resultPathAscii, &aWriter);
    man.WriteAddresses(resultPathHtml, &hWriter);
}