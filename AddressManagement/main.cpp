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

void CheckTest(bool condition, const std::string& testName)
{
    if (condition) std::cout << "[SUCCESS] " << testName << std::endl;
    else std::cerr << "[FAILED]  " << testName << std::endl;
}

void RunTestDriver();

int main()
{
    RunTestDriver();

    return 0;
}

void RunTestDriver()
{
    AddressManager man, noAddresses, empty;
    PersonReader pReader;
    AddressReader aReader;
    HtmlWriter hWriter;
    AsciiWriter aWriter;
    const std::string personPath{ "../../../pers.txt" };
    const std::string addressPath{ "../../../adr.txt" };
    const std::string resultPathHtml{ "../../../result.html" };
    const std::string resultPathAscii{ "../../../result.txt" };

    try { man.ReadFile(personPath, &pReader); man.ReadFile(addressPath, &aReader); CheckTest(true, "person and address file are read"); }
    catch (const std::exception&) { CheckTest(false, "person and address file are read"); }
    CheckTest(man.GetPersonCount() > 0 && man.GetAddressCount() > 0, "persons and addresses are stored");
    CheckTest(man.GetPerson(0).GetFirstName() == "Donald" && man.GetPerson(0).GetLastName() == "Duck" && man.GetPerson(0).GetAddressID() == 0, "first person is Donald Duck with address 0");
    CheckTest(man.GetAddress(0).GetStreet() == "Kellergasse" && man.GetAddress(0).GetNumber() == 3 && man.GetAddress(0).GetZip() == 4287 && man.GetAddress(0).GetCity() == "Radburg", "first address is Kellergasse 3, 4287 Radburg");
    try { man.WriteAddresses(resultPathAscii, &aWriter); man.WriteAddresses(resultPathHtml, &hWriter); CheckTest(true, "ascii and html file are written"); }
    catch (const std::exception&) { CheckTest(false, "ascii and html file are written"); }

    try 
    {
        man.ReadFile(personPath, nullptr); 
        CheckTest(false, "null reader -> invalid_argument"); 
    }
    catch (const std::invalid_argument&) 
    { CheckTest(true, "null reader -> invalid_argument"); }
    try 
    { man.WriteAddresses(resultPathAscii, nullptr); 
    CheckTest(false, "null writer -> invalid_argument"); }
    catch (const std::invalid_argument&) 
    { 
        CheckTest(true, "null writer -> invalid_argument"); 
    }
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
        man.ReadFile(personPath, &aReader); 
        CheckTest(false, "wrong line format -> runtime_error"); 
    }
    catch (const std::runtime_error&) 
    { 
        CheckTest(true, "wrong line format -> runtime_error"); 
    }
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
        empty.GetPerson(0); CheckTest(false, "wrong person index -> out_of_range");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "wrong person index -> out_of_range"); 
    }
    try 
    {
        noAddresses.ReadFile(personPath, &pReader);
        noAddresses.WriteAddresses(resultPathAscii, &aWriter); 
        CheckTest(false, "person without address -> out_of_range"); 
    }
    catch (const std::out_of_range&) 
    {
        CheckTest(true, "person without address -> out_of_range"); 
    }
}