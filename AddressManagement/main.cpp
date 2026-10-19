/// \file main.cpp
/// \brief Test driver. Runs all tests and prints the results.
/// \author Leander Kieweg, Julian Rieger

#include <iostream>
#include <string>

#include "Address.h"
#include "AddressManager.h"
#include "AsciiWriter.h"
#include "Person.h"

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

/// \brief Starts the program.
/// \return 0.
int main()
{
    AsciiWriter asciiWriter;
    AddressManager addressManager;
    Person person{"John", "Doe", 1};
    Address address{"Main St", 123, 12345, "Anytown"};
    addressManager.AddPerson(person);
    addressManager.AddAddress(address);
    addressManager.WriteAddresses("path", asciiWriter);

    std::cout << "Starting Property Management Test Driver..." << std::endl;
    return 0;
}