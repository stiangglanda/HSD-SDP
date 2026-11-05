/// @mainpage Graphic Management Test Driver
/// @brief Test driver for verifying the GraphicManagement system and SVG generation.
/// Tests blank and filled scenes, edge cases and exception handling.
///
/// @author Leander Kieweg, Julian Rieger
/// @date 05.11.2026
/// @version 1.0

#include <cstdint>
#include <cstdio>
#include <exception>
#include <iostream>
#include <string>
#include <stdexcept>
#include <new>
#include "BlankGraphicObjectFactory.h"
#include "FillGraphicObjectFactory.h"
#include "GraphicManagement.h"

/// @brief Returns a reproducible pseudo-random number in [lo, hi].
static int NextRandom(std::uint32_t& state, int lo, int hi)
{
    state = state * 1664525u + 1013904223u;
    return lo + static_cast<int>((state >> 8) %
        static_cast<std::uint32_t>(hi - lo + 1));
}

/// @returns the color as "#rrggbb" string.
static std::string Hex(int r, int g, int b)
{
    char buf[8];
    std::snprintf(buf, sizeof(buf), "#%02x%02x%02x", r, g, b);
    return buf;
}

/// @returns the linear interpolation of a and b (t in 0..100).
static int Mix(int a, int b, int t)
{
    return a + (b - a) * t / 100;
}

/// @brief Paints a night scene with more than 500 graphical objects.
static void PaintNightCity(GraphicManagement& gm)
{
    std::uint32_t randomState = 2026;

    // Sky
    for (int i = 0; i < 30; ++i) {
        int t = i * 100 / 29;
        gm.CreateRectangle(Hex(Mix(8, 232, t * t / 100), Mix(10, 120, t * t / 100), Mix(48, 90, t)),
            0, i * 14, 800, 14);
    }

    // Stars
    for (int i = 0; i < 220; ++i) {
        int x = NextRandom(randomState, 0, 800);
        int y = NextRandom(randomState, 0, 330);
        int size = NextRandom(randomState, 0, 9) == 0 ? 2 : 1;
        int bright = NextRandom(randomState, 170, 255);
        gm.CreateCircle(Hex(bright, bright, NextRandom(randomState, 190, 255)), x, y, size);
    }

    // Moon
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

    // Mountains
    for (int i = 0; i < 9; ++i)
        gm.CreateCircle("#3a2a5c", i * 100 - 20, 440, NextRandom(randomState, 70, 120));   // far row
    for (int i = 0; i < 6; ++i)
        gm.CreateCircle("#241a40", i * 150 + 30, 470, NextRandom(randomState, 60, 95));    // near row
    gm.CreateRectangle("#1b1432", 0, 440, 800, 160);                         // ground below mountains

    // Houses
    // 26 houses of width 30 side by side, the bottom edge is y = 520.
    for (int h = 0; h < 26; ++h) {
        int x = h * 31;
        int width = 30;
        int height = NextRandom(randomState, 90, 250);
        int top = 520 - height;
        int shade = NextRandom(randomState, 0, 24);

        gm.CreateRectangle(Hex(34 + shade, 28 + shade, 66 + shade), x, top, width, height);  // wall
        gm.CreateRectangle(Hex(60 + shade, 40 + shade, 90 + shade), x - 1, top - 5, width + 2, 6); // roof edge
        if (NextRandom(randomState, 0, 2) == 0)
            gm.CreateRectangle("#120d26", x + 20, top - 16, 5, 12);                          // chimney

        // windows: 2 columns, a new row every 14 pixels
        for (int wy = top + 10; wy < 512; wy += 14) {
            for (int wx = x + 6; wx < x + width - 6; wx += 12) {
                bool lit = NextRandom(randomState, 0, 99) < 62;
                std::string color = lit ? Hex(255, NextRandom(randomState, 200, 235), NextRandom(randomState, 80, 140))
                    : Hex(18, 16, 40);
                gm.CreateRectangle(color, wx, wy, 7, 8);
            }
        }
    }

    // Street
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

/// @brief Paints a neon cyberpunk scene.
static void PaintCyberpunk(GraphicManagement& gm)
{
    gm.CreateRectangle("#09001f", 0, 0, 600, 400);
    gm.CreateCircle("#160d45", 300, 135, 150);
    gm.CreateCircle("#ff2bd6", 300, 135, 120);
    gm.CreateCircle("#09001f", 300, 135, 104);

    for (int i = 0; i < 9; ++i) {
        int x = i * 75 - 10;
        int height = 80 + (i % 4) * 28;
        gm.CreateRectangle("#17103d", x, 360 - height, 60, height);
        gm.CreateRectangle("#00e5ff", x + 12, 340 - height, 5, 12);
        gm.CreateRectangle("#ff2bd6", x + 32, 315 - height, 5, 18);
    }

    gm.CreateRectangle("#241553", 0, 360, 600, 40);
    for (int i = 0; i < 10; ++i) {
        gm.CreateRectangle("#00e5ff", i * 68 + 8, 378, 38, 3);
        gm.CreateCircle("#ff2bd6", i * 68 + 52, 367, 4);
    }
}

/// @brief Runs the edge-case and exception tests.
static bool TestEdgeCases(GraphicManagement& gm)
{
    bool passed = true;

    gm.AddImage(FillGraphicObjectFactory::GetInstance(), "test-1-element.svg");
    gm.CreateCircle("#ff0000", 100, 100, 50);
    gm.AddImage(BlankGraphicObjectFactory::GetInstance(), "test-empty-image.svg");
    gm.WriteSVG();
    std::cout << "[PASS] Single-element and empty-image tests\n";

    try {
        gm.CreateCircle("#000000", 10, 10, 0);
        passed = false;
        std::cerr << "[FAIL] Zero-radius circle was accepted\n";
    }
    catch (const std::invalid_argument&) {
        std::cout << "[PASS] Zero-radius circle rejected\n";
    }

    try {
        gm.AddImage(BlankGraphicObjectFactory::GetInstance(),
            "Y:/this/directory/does/not/exist/test.svg");
        gm.WriteSVG();
        passed = false;
        std::cerr << "[FAIL] Invalid file path was accepted\n";
    }
    catch (const std::runtime_error&) {
        std::cout << "[PASS] Invalid file path rejected\n";
    }

    return passed;
}

int main()
{
    try {
        auto& gm = GraphicManagement::GetInstance();

        gm.AddImage(BlankGraphicObjectFactory::GetInstance(), "blank-nightcity.svg");
        PaintNightCity(gm);
        gm.AddImage(FillGraphicObjectFactory::GetInstance(), "filled-nightcity.svg");
        PaintNightCity(gm);

        gm.AddImage(BlankGraphicObjectFactory::GetInstance(), "blank-cyberpunk.svg");
        PaintCyberpunk(gm);
        gm.AddImage(FillGraphicObjectFactory::GetInstance(), "filled-cyberpunk.svg");
        PaintCyberpunk(gm);

        gm.WriteSVG();
        std::cout << "[PASS] Scene generation and SVG export\n";
        if (!TestEdgeCases(gm))
            return 1;
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "[FAIL] Memory allocation: " << e.what() << '\n';
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "[FAIL] Test driver: " << e.what() << '\n';
        return 1;
    }

    std::cout << "[PASS] All tests\n";
    return 0;
}
