#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <new>
#include "BlankGraphicObjectFactory.h"
#include "FillGraphicObjectFactory.h"
#include "GraphicManagement.h"

namespace
{
    /// @brief Simple deterministic random number generator (LCG).
    ///
    /// A fixed seed is used on purpose: the blank and the filled image are
    /// painted by two separate calls and must show exactly the same scene.
    class Random
    {
    public:
        explicit Random(std::uint32_t seed) : mState{ seed } {}

        /// @returns a number in the range [lo, hi].
        int Next(int lo, int hi)
        {
            mState = mState * 1664525u + 1013904223u;
            return lo + static_cast<int>((mState >> 8) % static_cast<std::uint32_t>(hi - lo + 1));
        }

    private:
        std::uint32_t mState;
    };

    /// @returns the color as "#rrggbb" string.
    std::string Hex(int r, int g, int b)
    {
        char buf[8];
        std::snprintf(buf, sizeof(buf), "#%02x%02x%02x", r, g, b);
        return buf;
    }

    /// @returns the linear interpolation of a and b (t in 0..100).
    int Mix(int a, int b, int t)
    {
        return a + (b - a) * t / 100;
    }
} // namespace

/// @brief Paints a night scene (800 x 600) with far more than 500 shapes.
///
/// Layers (painter's algorithm, later objects cover earlier ones):
///   1. sky as 30 horizontal color bands (gradient)    ->  30 shapes
///   2. 220 stars                                       -> 220 shapes
///   3. moon with halo and craters                      ->  12 shapes
///   4. mountain range                                  ->  15 shapes
///   5. 26 houses with roofs, chimneys and windows      -> ~600 shapes
///   6. street with lamps and their light cones         ->  ~60 shapes
static void PaintNightCity(GraphicManagement& gm)
{
    Random rnd{ 2026 };

    // ---------- 1. Sky gradient: deep blue on top, orange at the horizon ----------
    for (int i = 0; i < 30; ++i) {
        int t = i * 100 / 29;
        gm.CreateRectangle(Hex(Mix(8, 232, t * t / 100), Mix(10, 120, t * t / 100), Mix(48, 90, t)),
            0, i * 14, 800, 14);
    }

    // ---------- 2. Stars (more and bigger ones in the upper sky) ----------
    for (int i = 0; i < 220; ++i) {
        int x = rnd.Next(0, 800);
        int y = rnd.Next(0, 330);
        int size = rnd.Next(0, 9) == 0 ? 2 : 1;
        int bright = rnd.Next(170, 255);
        gm.CreateCircle(Hex(bright, bright, rnd.Next(190, 255)), x, y, size);
    }

    // ---------- 3. Moon ----------
    gm.CreateCircle("#2a3a78", 630, 110, 78);   // outer halo
    gm.CreateCircle("#3d4f95", 630, 110, 62);
    gm.CreateCircle("#f5f0c8", 630, 110, 46);   // moon disc
    gm.CreateCircle("#e3dcae", 612, 96, 11);    // craters
    gm.CreateCircle("#e3dcae", 650, 124, 9);
    gm.CreateCircle("#e3dcae", 640, 84, 6);
    gm.CreateCircle("#e3dcae", 618, 130, 7);
    gm.CreateCircle("#d8d09a", 660, 100, 5);
    gm.CreateCircle("#d8d09a", 600, 116, 4);
    gm.CreateCircle("#fffbe0", 598, 90, 3);     // highlights
    gm.CreateCircle("#fffbe0", 660, 140, 3);

    // ---------- 4. Mountains: overlapping circles, two rows ----------
    for (int i = 0; i < 9; ++i)
        gm.CreateCircle("#3a2a5c", i * 100 - 20, 440, rnd.Next(70, 120));   // far row
    for (int i = 0; i < 6; ++i)
        gm.CreateCircle("#241a40", i * 150 + 30, 470, rnd.Next(60, 95));    // near row
    gm.CreateRectangle("#1b1432", 0, 440, 800, 160);                         // ground below mountains

    // ---------- 5. Houses ----------
    // 26 houses of width 30 side by side, the bottom edge is y = 520.
    for (int h = 0; h < 26; ++h) {
        int x = h * 31;
        int width = 30;
        int height = rnd.Next(90, 250);
        int top = 520 - height;
        int shade = rnd.Next(0, 24);

        gm.CreateRectangle(Hex(34 + shade, 28 + shade, 66 + shade), x, top, width, height);  // wall
        gm.CreateRectangle(Hex(60 + shade, 40 + shade, 90 + shade), x - 1, top - 5, width + 2, 6); // roof edge
        if (rnd.Next(0, 2) == 0)
            gm.CreateRectangle("#120d26", x + 20, top - 16, 5, 12);                          // chimney

        // windows: 2 columns, a new row every 14 pixels
        for (int wy = top + 10; wy < 512; wy += 14) {
            for (int wx = x + 6; wx < x + width - 6; wx += 12) {
                bool lit = rnd.Next(0, 99) < 62;
                std::string color = lit ? Hex(255, rnd.Next(200, 235), rnd.Next(80, 140))
                    : Hex(18, 16, 40);
                gm.CreateRectangle(color, wx, wy, 7, 8);
            }
        }
    }

    // ---------- 6. Street, lamps and puddles ----------
    gm.CreateRectangle("#2b2342", 0, 520, 800, 80);          // street
    gm.CreateRectangle("#4a3f6b", 0, 520, 800, 4);           // curb
    for (int i = 0; i < 8; ++i) {
        int x = 50 + i * 100;
        gm.CreateRectangle("#0e0a1e", x, 470, 4, 75);        // lamp post
        gm.CreateCircle("#fff2a8", x + 2, 466, 5);           // lamp
        gm.CreateCircle("#c9b25a", x + 2, 530, 24);          // light on the street
        gm.CreateCircle("#ffe98a", x + 2, 530, 14);
    }
    for (int i = 0; i < 12; ++i)                             // road markings
        gm.CreateRectangle("#8e86ad", i * 70 + 10, 565, 36, 4);
}

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