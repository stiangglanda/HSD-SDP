/// \file main.cpp
/// \brief Simple test driver for the address management.
/// \author Leander Kieweg, Julian Rieger
///
/// The driver creates its input files itself and removes all files at the end.

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Address.h"
#include "AddressManager.h"
#include "AddressReader.h"
#include "AsciiWriter.h"
#include "HtmlWriter.h"
#include "Person.h"
#include "PersonReader.h"

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

/// \brief Helper function that creates a text file.
void CreateFile(const std::string& path, const std::string& content)
{
    std::ofstream out(path);
    out << content;
}

/// \brief Helper function that returns the content of a text file.
std::string ReadAll(const std::string& path)
{
    std::ifstream in(path);
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

/// \brief Tests reading and writing with valid files.
void TestValidCase()
{
    CreateFile("pers.txt", "# Datei: pers.txt\n# erstellt am: 01.10.2022\n"
        "Donald Duck 0\nDagobert Duck 1\nDaniel Duesentrieb 2\nMax Moechtegern 2\n");
    CreateFile("pers2.txt", "Brid Patt 0\nJack Unterweger 1\nFrank Gust 2\n");
    CreateFile("adr.txt", "# Datei: adr.txt\n"
        "Kellergasse 3 4287 Radburg\nDiemstrasse 1 2345 Hinterhof\n"
        "Waldstrasse 45 6785 Burghausen\nDomweg 123 9865 Mixbergen\n");

    AddressManager man;
    PersonReader pReader;
    AddressReader aReader;
    AsciiWriter aWriter;
    HtmlWriter hWriter;

    // Same order as in the exercise: the persons are read before the addresses.
    man.ReadFile("pers.txt", &pReader);
    man.ReadFile("pers2.txt", &pReader);
    man.ReadFile("adr.txt", &aReader);

    CheckTest(man.GetPersonCount() == 7, "7 persons read");
    CheckTest(man.GetAddressCount() == 4, "4 addresses read");
    CheckTest(man.GetPerson(0).GetFirstName() == "Donald" && man.GetPerson(0).GetLastName() == "Duck",
        "first person is Donald Duck");
    CheckTest(man.GetPerson(4).GetAddressID() == 0, "Brid Patt (second file) refers to address 0");
    CheckTest(man.GetAddress(0).GetStreet() == "Kellergasse" && man.GetAddress(0).GetNumber() == 3
        && man.GetAddress(0).GetZip() == 4287 && man.GetAddress(0).GetCity() == "Radburg",
        "first address is Kellergasse 3, 4287 Radburg");

    man.WriteAddresses("result.txt", &aWriter);
    man.WriteAddresses("result.html", &hWriter);

    CheckTest(ReadAll("result.txt") ==
        "Adressen mit zugeordneten Personen\n"
        "----------------------------------\n"
        "4287 Radburg\nKellergasse 3\n    Donald Duck\n    Brid Patt\n\n"
        "2345 Hinterhof\nDiemstrasse 1\n    Dagobert Duck\n    Jack Unterweger\n\n"
        "6785 Burghausen\nWaldstrasse 45\n    Daniel Duesentrieb\n    Max Moechtegern\n    Frank Gust\n\n"
        "9865 Mixbergen\nDomweg 123\n\n",
        "ascii file has the expected content");
    std::string html = ReadAll("result.html");
    CheckTest(html.find("<i>4287 Radburg<br>") != std::string::npos
        && html.find("Donald Duck<br>") != std::string::npos
        && html.find("</html>") != std::string::npos,
        "html file has the expected content");
}

/// \brief Tests that wrong usage throws the expected exceptions and that we catch them.
void TestErrors()
{
    AddressManager man;
    PersonReader pReader;
    AddressReader aReader;
    AsciiWriter aWriter;

    try
    {
        man.ReadFile("pers.txt", nullptr);
        CheckTest(false, "null reader throws invalid_argument");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "null reader throws invalid_argument");
    }

    try
    {
        man.ReadFile("no_such_file.txt", &pReader);
        CheckTest(false, "missing file throws runtime_error");
    }
    catch (const std::runtime_error&)
    {
        CheckTest(true, "missing file throws runtime_error");
    }

    try
    {
        man.ReadFile("pers.txt", &aReader);   // person file read with the address reader
        CheckTest(false, "wrong line format throws runtime_error");
    }
    catch (const std::runtime_error&)
    {
        CheckTest(true, "wrong line format throws runtime_error");
    }

    try
    {
        man.WriteAddresses("result.txt", nullptr);
        CheckTest(false, "null writer throws invalid_argument");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "null writer throws invalid_argument");
    }

    try
    {
        man.GetAddress(0);   // manager has no address yet
        CheckTest(false, "wrong index throws out_of_range");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "wrong index throws out_of_range");
    }

    try
    {
        // The person refers to address 5, but only one address exists.
        CreateFile("bad_pers.txt", "Hans Fehler 5\n");
        CreateFile("bad_adr.txt", "Hauptstrasse 1 1000 Wien\n");
        man.ReadFile("bad_pers.txt", &pReader);
        man.ReadFile("bad_adr.txt", &aReader);
        man.WriteAddresses("bad_result.txt", &aWriter);
        CheckTest(false, "invalid address index throws out_of_range");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "invalid address index throws out_of_range");
    }
}

/// \brief Starts the program.
/// \return 0.
int main()
{
    TestValidCase();
    TestErrors();

    // Remove all files created by the tests.
    std::remove("pers.txt");
    std::remove("pers2.txt");
    std::remove("adr.txt");
    std::remove("result.txt");
    std::remove("result.html");
    std::remove("bad_pers.txt");
    std::remove("bad_adr.txt");
    std::remove("bad_result.txt");

    return 0;
}