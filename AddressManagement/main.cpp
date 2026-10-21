/// @mainpage Address Management Test Driver
/// @brief Test driver for verifying the AddressManagement system.
/// 
/// Tests the reading of person and address files using different Reader implementations,
/// verifies the integrity of the data stored in the AddressManager, and tests exporting
/// using AsciiWriter and HtmlWriter. Additionally, all relevant exception cases 
/// (invalid arguments, runtime errors, out-of-range accesses) are thoroughly verified.
/// 
/// @author Leander Kieweg, Julian Rieger
/// @date 21.10.2026
/// @version 1.0

#include <iostream>
#include <stdexcept>
#include <string>

#include "Address.h"
#include "AddressManager.h"
#include "AddressReader.h"
#include "AsciiWriter.h"
#include "HtmlWriter.h"
#include "Person.h"
#include "PersonReader.h"

/// @brief Evaluates a test condition and prints a formatted status message to the console.
/// 
/// If the condition is true, prints "[SUCCESS]" to standard output (std::cout).
/// If false, prints "[FAILED]" to standard error (std::cerr).
/// 
/// @param[in] condition The boolean test result to verify.
/// @param[in] testName The descriptive name or purpose of the test.
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

/// @brief Executes the entire test suite for the address management system.
void RunTestDriver();

/// @brief Program entry point. Runs the test driver.
/// @return 0 upon completion.
int main()
{
    RunTestDriver();
    return 0;
}

/// @brief Implementation of the test suite.
/// 
/// Tests the regular workflow (reading files, checking data, writing output)
/// followed by comprehensive negative tests verifying expected exceptions:
/// - std::invalid_argument when passing nullptr
/// - std::runtime_error on non-existent files or corrupt line formats
/// - std::out_of_range when accessing invalid indices or missing address relations
void RunTestDriver()
{
    AddressManager man;
    AddressManager noAddresses;
    AddressManager empty;

    PersonReader pReader;
    AddressReader aReader;
    HtmlWriter hWriter;
    AsciiWriter aWriter;

    const std::string personPath{ "../../../pers.txt" };
    const std::string addressPath{ "../../../adr.txt" };
    const std::string resultPathHtml{ "../../../result.html" };
    const std::string resultPathAscii{ "../../../result.txt" };

    try
    {
        man.ReadFile(personPath, &pReader);
        man.ReadFile(addressPath, &aReader);
        CheckTest(true, "person and address file are read");
    }
    catch (const std::exception&)
    {
        CheckTest(false, "person and address file are read");
    }

    // Check count of stored elements
    bool const hasEntries = (man.GetPersonCount() > 0) && (man.GetAddressCount() > 0);
    CheckTest(hasEntries, "persons and addresses are stored");

    // Verify first person
    const Person& firstPerson = man.GetPerson(0);
    bool const isDonaldDuck = (firstPerson.GetFirstName() == "Donald") &&
                              (firstPerson.GetLastName() == "Duck") &&
                              (firstPerson.GetAddressID() == 0);
    CheckTest(isDonaldDuck, "first person is Donald Duck with address 0");

    // Verify first address
    const Address& firstAddress = man.GetAddress(0);
    bool const isExpectedAddress = (firstAddress.GetStreet() == "Kellergasse") &&
                                   (firstAddress.GetNumber() == 3) &&
                                   (firstAddress.GetZip() == 4287) &&
                                   (firstAddress.GetCity() == "Radburg");
    CheckTest(isExpectedAddress, "first address is Kellergasse 3, 4287 Radburg");

    try
    {
        man.WriteAddresses(resultPathAscii, &aWriter);
        man.WriteAddresses(resultPathHtml, &hWriter);
        CheckTest(true, "ascii and html file are written");
    }
    catch (const std::exception&)
    {
        CheckTest(false, "ascii and html file are written");
    }

    // Exception Handling Tests: std::invalid_argument
    try
    {
        man.ReadFile(personPath, nullptr);
        CheckTest(false, "null reader -> invalid_argument");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "null reader -> invalid_argument");
    }

    try
    {
        man.WriteAddresses(resultPathAscii, nullptr);
        CheckTest(false, "null writer -> invalid_argument");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "null writer -> invalid_argument");
    }

    // Exception Handling Tests: std::runtime_error
    try
    {
        man.ReadFile("no_such_file.txt", &pReader);
        CheckTest(false, "missing file -> runtime_error");
    }
    catch (const std::runtime_error&)
    {
        CheckTest(true, "missing file -> runtime_error");
    }

    try
    {
        // Parsing person file with address reader -> mismatching format
        man.ReadFile(personPath, &aReader);
        CheckTest(false, "wrong line format -> runtime_error");
    }
    catch (const std::runtime_error&)
    {
        CheckTest(true, "wrong line format -> runtime_error");
    }

    // Exception Handling Tests: std::out_of_range
    try
    {
        man.GetAddress(man.GetAddressCount());
        CheckTest(false, "wrong address index -> out_of_range");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "wrong address index -> out_of_range");
    }

    try
    {
        empty.GetPerson(0);
        CheckTest(false, "wrong person index -> out_of_range");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "wrong person index -> out_of_range");
    }

    try
    {
        // Person references address ID that was never loaded
        noAddresses.ReadFile(personPath, &pReader);
        noAddresses.WriteAddresses(resultPathAscii, &aWriter);
        CheckTest(false, "person without address -> out_of_range");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "person without address -> out_of_range");
    }
}