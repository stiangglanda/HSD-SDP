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

/// \brief Starts the program.
/// \return 0.
int main()
{
    std::cout << "Starting Property Management Test Driver..." << std::endl;
    return 0;
}