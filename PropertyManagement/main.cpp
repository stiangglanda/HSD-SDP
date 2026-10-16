/// \file main.cpp
/// \brief Test driver. Runs all tests and prints the results.
/// \author Leander Kieweg, Julian Rieger

#include "PropertyManagement.h"
#include <iostream>
#include <string>

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
    // Test data setup
    Tenant t1{ "Hubert", "von Goisern", 1960 };
    Tenant t2{ "Jakob", "Schubert", 1990 };
    Tenant t3{ "Ayrton", "Senna", 1950 };
    Tenant t4{ "Maximilian", "Laimer", 1960 };
    Tenant t5{ "Leander", "Mueller", 2000 };
    Tenant t6{ "Manuel", "Hundstorfer", 1995 };
    Tenant t7{ "Daniel", "Moser", 1949 };

    Flat f1{ 1, 45.0f, false, &t1 };
    Flat f2{ 2, 90.0f, true, &t2 };
    Flat f3{ 3, 63.5f, false, &t3 };
    Flat f4{ 4, 105.0f, true }; // Empty flat
    Flat f5{ 1, 39.0f, true, &t4 };
    Flat f6{ 2, 65.0f, false, &t5 };
    Flat f7{ 3, 70.0f, true, &t6 };
    Flat f8{ 4, 70.0f, true, &t6 };

    std::vector<Flat> floor1{ f1, f2 };
    std::vector<Flat> floor2{ f3, f4 };
    std::vector<Flat> floor3{ f5, f6 };
    std::vector<Flat> floor4{ f7, f8 };

    Floor e1{ 0, floor1 };
    Floor e2{ 1, floor2 };
    Floor e3{ 0, floor3 };
    Floor e4{ 1, floor4 };

    std::vector<Floor> house1{ e1, e2 };
    std::vector<Floor> house2{ e3, e4 };

    House h1{ {"Softwarepark 47", "4232", "Hagenberg"}, house1 };
    House h2{ {"Musterstrasse 14", "4711", "Linz"}, house2 };

    PropertyManagement prop;
    prop.AddHouse(h1);
    prop.AddHouse(h2);

    // Demonstration output
    prop.Print();
    std::cout << std::endl;

    // Getter tests
    CheckTest(h1.GetAddress().GetCity() == "Hagenberg", "Address::GetCity()");
    CheckTest(h1.GetAddress().GetStreet() == "Softwarepark 47", "Address::GetStreet()");
    CheckTest(h1.GetAddress().GetZip() == "4232", "Address::GetZip()");
    CheckTest(h1.GetFloorCount() == 2, "House::GetFloorCount()");

    CheckTest(e1.GetNumber() == 0, "Floor::GetNumber()");
    CheckTest(e1.GetFlatCount() == 2, "Floor::GetFlatCount()");

    CheckTest(e1.GetFlat(1).GetNumber() == 1, "Floor::GetFlat(1).GetNumber()");
    CheckTest(e1.GetFlat(1).GetArea() == 45.0f, "Flat::GetArea()");
    CheckTest(e1.GetFlat(1).HasBalcony() == false, "Flat::HasBalcony()");
    CheckTest(e1.GetFlat(2).HasBalcony() == true, "Flat::HasBalcony()");

    CheckTest(e1.GetFlat(1).GetTenant() != nullptr, "Flat::GetTenant() != nullptr");
    CheckTest(e1.GetFlat(1).GetTenant()->GetBirthYear() == 1960, "Tenant::GetBirthYear()");
    CheckTest(e1.GetFlat(1).GetTenant()->GetFirstName() == "Hubert", "Tenant::GetFirstName()");
    CheckTest(e1.GetFlat(1).GetTenant()->GetLastName() == "von Goisern", "Tenant::GetLastName()");

    const Floor& constFloorRef = e1;
    CheckTest(constFloorRef.GetFlat(1).GetNumber() == 1, "Floor::GetFlat() const overload");

    // Changing tenant
    e1.GetFlat(1).SetTenant(&t7);
    CheckTest(e1.GetFlat(1).GetTenant() == &t7, "Flat::SetTenant(newTenant)");

    e1.GetFlat(1).SetTenant(nullptr);
    CheckTest(e1.GetFlat(1).GetTenant() == nullptr, "Flat::SetTenant(nullptr)");

    e1.GetFlat(1).SetTenant(&t1);
    CheckTest(e1.GetFlat(1).GetTenant() == &t1, "Flat::SetTenant(restore)");

    // Exception tests
    try
    {
        House invalidHouse{ {"", "4711", "Hagenberg"}, house1 };
        CheckTest(false, "Address throws invalid_argument on empty street");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "Address throws invalid_argument on empty street");
    }

    try
    {
        std::vector<Floor> emptyFloors{};
        House invalidHouse{ {"Softwarepark 11", "4711", "Hagenberg"}, emptyFloors };
        CheckTest(false, "House throws invalid_argument on empty floors");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "House throws invalid_argument on empty floors");
    }

    try
    {
        std::vector<Flat> emptyFlats{};
        Floor invalidFloor{ 0, emptyFlats };
        CheckTest(false, "Floor throws invalid_argument on empty flats");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "Floor throws invalid_argument on empty flats");
    }

    try
    {
        e1.GetFlat(999);
        CheckTest(false, "Floor::GetFlat throws out_of_range for missing door number");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "Floor::GetFlat throws out_of_range for missing door number");
    }

    try
    {
        prop.AddHouse(h1);
        CheckTest(false, "PropertyManagement::AddHouse throws on duplicate address");
    }
    catch (const std::invalid_argument&)
    {
        CheckTest(true, "PropertyManagement::AddHouse throws on duplicate address");
    }

    CheckTest(prop.GetHouseCount() == 2, "PropertyManagement count before removal == 2");
    prop.RemoveHouse(h1.GetAddress());
    CheckTest(prop.GetHouseCount() == 1, "PropertyManagement::RemoveHouse reduces count to 1");

    try
    {
        prop.RemoveHouse(h1.GetAddress());
        CheckTest(false, "PropertyManagement::RemoveHouse throws on unknown address");
    }
    catch (const std::out_of_range&)
    {
        CheckTest(true, "PropertyManagement::RemoveHouse throws on unknown address");
    }
}