#include <exception>
#include <iostream>
#include "BlankGraphicsObjectFactory.h"
#include "FillGraphicsObjectFactory.h"
#include "GraphicsManagement.h"

/// @author Leander Kieweg
/// @date 05.11.2026
/// @brief Test driver: creates one image with not filled and one with filled objects.
int main()
{
    try {
        auto& gm = GraphicsManagement::GetInstance();

        // Outline version: a neon portal above a futuristic skyline.
        gm.AddImage(BlankGraphicsObjectFactory::GetInstance(), "blank-cyberpunk.svg");
        gm.CreateRectangle("#09001f", 0, 0, 600, 400);
        gm.CreateCircle("#ff2bd6", 300, 135, 120);
        gm.CreateCircle("#00f5ff", 300, 135, 95);
        gm.CreateCircle("#ffe600", 300, 135, 68);
        gm.CreateCircle("#ff6b00", 300, 135, 40);
        gm.CreateRectangle("#00f5ff", 35, 245, 70, 155);
        gm.CreateRectangle("#ff2bd6", 125, 210, 80, 190);
        gm.CreateRectangle("#ffe600", 225, 270, 65, 130);
        gm.CreateRectangle("#00f5ff", 315, 225, 95, 175);
        gm.CreateRectangle("#ff2bd6", 435, 185, 125, 215);
        gm.CreateRectangle("#ff6b00", 55, 280, 30, 55);
        gm.CreateRectangle("#ff6b00", 145, 245, 35, 55);
        gm.CreateRectangle("#00f5ff", 245, 300, 25, 45);
        gm.CreateRectangle("#ffe600", 345, 260, 35, 55);
        gm.CreateRectangle("#ff6b00", 475, 220, 45, 65);
        gm.CreateCircle("#ff2bd6", 300, 365, 155);
        gm.CreateCircle("#00f5ff", 300, 365, 115);

        // Filled version: the same scene with intense neon colors.
        gm.AddImage(FillGraphicsObjectFactory::GetInstance(), "filled-cyberpunk.svg");
        gm.CreateRectangle("#09001f", 0, 0, 600, 400);
        gm.CreateCircle("#ff2bd6", 300, 135, 120);
        gm.CreateCircle("#00f5ff", 300, 135, 95);
        gm.CreateCircle("#ffe600", 300, 135, 68);
        gm.CreateCircle("#ff6b00", 300, 135, 40);
        gm.CreateRectangle("#16004a", 35, 245, 70, 155);
        gm.CreateRectangle("#25005e", 125, 210, 80, 190);
        gm.CreateRectangle("#32006b", 225, 270, 65, 130);
        gm.CreateRectangle("#1b0a63", 315, 225, 95, 175);
        gm.CreateRectangle("#3b075f", 435, 185, 125, 215);
        gm.CreateRectangle("#ff6b00", 55, 280, 30, 55);
        gm.CreateRectangle("#ffe600", 145, 245, 35, 55);
        gm.CreateRectangle("#ff2bd6", 245, 300, 25, 45);
        gm.CreateRectangle("#00f5ff", 345, 260, 35, 55);
        gm.CreateRectangle("#ff6b00", 475, 220, 45, 65);
        gm.CreateCircle("#4c1d95", 300, 365, 155);
        gm.CreateCircle("#312e81", 300, 365, 115);

        gm.WriteSVG();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Created blank-cyberpunk.svg and filled-cyberpunk.svg\n";
    return 0;
}
