#include <exception>
#include <iostream>
#include <stdexcept>
#include <new>
#include "BlankGraphicObjectFactory.h"
#include "FillGraphicObjectFactory.h"
#include "GraphicManagement.h"

/// @author Leander Kieweg
/// @date 05.11.2026
/// @brief Test driver: creates images and tests functionality/error handling.
int main()
{
    // ==========================================
    // TEST 1: Happy Path & Regular Functionality
    // ==========================================
    try {
        auto& gm = GraphicManagement::GetInstance();

        // Outline version: a neon portal above a futuristic skyline.
        gm.AddImage(BlankGraphicObjectFactory::GetInstance(), "blank-cyberpunk.svg");
        gm.CreateRectangle("#09001f", 0, 0, 600, 400);
        gm.CreateCircle("#ff2bd6", 300, 135, 120);

        // ---> HIER WIEDER DEINE RESTLICHEN KREISE & RECHTECKE EINFÜGEN <---

        // Filled version: the same scene with intense neon colors.
        gm.AddImage(FillGraphicObjectFactory::GetInstance(), "filled-cyberpunk.svg");
        gm.CreateRectangle("#09001f", 0, 0, 600, 400);
        gm.CreateCircle("#ff2bd6", 300, 135, 120);

        // ---> HIER WIEDER DEINE RESTLICHEN KREISE & RECHTECKE EINFÜGEN <---


        // --- Checklist Test Cases (1 element & empty container) ---

        // Test: Container with exactly 1 element
        gm.AddImage(FillGraphicObjectFactory::GetInstance(), "test-1-element.svg");
        gm.CreateCircle("#ff0000", 100, 100, 50);

        // Test: Empty container (0 elements)
        gm.AddImage(BlankGraphicObjectFactory::GetInstance(), "test-empty-image.svg");
        // Intentionally not adding any objects here!

        gm.WriteSVG();
        std::cout << "[SUCCESS] Images generated successfully.\n";

    } catch (const std::bad_alloc& e) {
        std::cerr << "[FATAL ERROR] Memory allocation failed: " << e.what() << "\n";
        return 1;
    } catch (const std::exception &e) {
        std::cerr << "[ERROR] " << e.what() << "\n";
        return 1;
    }

    // ==========================================
    // TEST 2: Provoke and catch errors
    // ==========================================

    // Test: Check parameter validity (Checklist point 21)
    try {
        auto& gm = GraphicManagement::GetInstance();
        std::cout << "Test: Attempting to create a circle with radius 0...\n";
        gm.CreateCircle("#000000", 10, 10, 0); // Should throw an exception
        std::cerr << "[FAIL] No exception thrown for radius 0!\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "[EXPECTED] Exception caught: " << e.what() << "\n";
    }

    // Test: Empty/Invalid file path (Checklist point 21)
    try {
        auto& gm = GraphicManagement::GetInstance();
        std::cout << "Test: Attempting to save to an invalid path...\n";
        // An illegal path that should fail on any OS
        gm.AddImage(BlankGraphicObjectFactory::GetInstance(), "Y:/this/directory/does/not/exist/test.svg");
        gm.WriteSVG();
        std::cerr << "[FAIL] File could be saved to an invalid path!\n";
    } catch (const std::runtime_error& e) {
        std::cout << "[EXPECTED] Exception caught: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "[EXPECTED] Exception caught: " << e.what() << "\n";
    }

    std::cout << "\nAll tests completed.\n";
    return 0;
}