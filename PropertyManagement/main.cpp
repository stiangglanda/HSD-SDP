/// \file main.cpp
/// \brief Test driver. Runs all tests and prints the results.
/// \author Leander Kieweg, Julian Rieger

#include "PropertyManagement.h"
#include <iostream>


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
    Tenant t1{ "Hubert", "von Goisern", 1960 };
    Tenant t2{ "Jakob", "Schubert", 1990 };
    Tenant t3{ "Ayrton", "Senna", 1950 };
    Tenant t4{ "Maximilian", "Laimer", 1960 };
    Tenant t5{ "Leander", "M�ller", 2000 };
    Tenant t6{ "Manuel", "Hundstorfer", 1995 };
    Tenant t7{ "Daniel", "Moser", 1949 };

    Flat f1{ 1, 45.0f, false, &t1 };
    Flat f2{ 2, 90.0f, true, &t2 };
    Flat f3{ 3, 63.5f, false, &t3 };
    Flat f4{ 4, 105.0f, true };
    Flat f5{ 1, 39.0f, true, &t4 };
    Flat f6{ 2, 65.0f, false, &t5 };
    Flat f7{ 3, 70.0f, true, &t6 };
    Flat f8{ 4, 70.0f, true, &t6 };
    
    std::vector<Flat> floor1{ f1,f2 };
    std::vector<Flat> floor2{ f3,f4 };
    std::vector<Flat> floor3{ f5,f6 };
    std::vector<Flat> floor4{ f7,f8 };
    Floor e1{ 1,floor1 };
    Floor e2{ 2,floor2 };
    Floor e3{ 1,floor3 };
    Floor e4{ 2,floor4 };

    std::vector<Floor> house1{ e1, e2 };
    std::vector<Floor> house2{ e3, e4 };
    House h1{ {"Softwarepark 47", "4232", "Hagenberg"}, house1 };
    House h2{ {"Musterstrasse 14", "4711", "Linz"}, house2 };

    PropertyManagement prop;

    prop.AddHouse(h1);
    prop.AddHouse(h2);

    prop.Print();

    std::cout << std::endl;
    if (h1.GetAddress().GetCity() == "Hagenberg") std::cout << "Getter GetCity passed." << std::endl;
    if (h1.GetAddress().GetStreet() == "Softwarepark 47") std::cout << "Getter GetStreet passed." << std::endl;
    if (h1.GetAddress().GetZip() == "4232") std::cout << "Getter GetZip passed." << std::endl;
    if (e1.GetFlatCount() == 2) std::cout << "Getter GetFlatCount passed." << std::endl;
    if (e1.GetFlat(1).GetNumber() == 1) std::cout << "Getter GetFlat && GetNumber passed." << std::endl;
    if (e1.GetFlat(1).GetArea() == 45.0f) std::cout << "Getter GetFlat && GetArea passed." << std::endl;
    if (e1.GetFlat(1).GetTenant()->GetBirthYear() == 1960) std::cout << "Getter GetTenant && GetBirthYear passed." << std::endl;
    if (e1.GetFlat(1).GetTenant()->GetFirstName() == "Hubert") std::cout << "Getter GetTenant && GetFirstName passed." << std::endl;
    if (e1.GetFlat(1).GetTenant()->GetLastName() == "von Goisern") std::cout << "Getter GetTenant && GetLastName passed." << std::endl;

    try
    {
        House h11{ {"", "4711", "Hagenberg"}, house1 };
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Catching Error for empty Address: passed." << std::endl;
    try
    {
        std::vector<Floor> emptyhouse{};
        House h11{ {"Softwarepark 11", "4711", "Hagenberg"}, emptyhouse };
    }
    catch (std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << "Catching Error for empty house vector: passed.";

}