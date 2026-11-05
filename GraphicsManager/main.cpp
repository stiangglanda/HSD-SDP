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

        gm.AddImage(BlankGraphicsObjectFactory::GetInstance(), "blank-landscape.svg");
        gm.CreateCircle("#1d4ed8", 150, 100, 70);
        gm.CreateCircle("#f97316", 150, 100, 45);
        gm.CreateRectangle("#166534", 40, 190, 220, 80);
        gm.CreateRectangle("#7c3aed", 75, 215, 150, 35);

        gm.AddImage(FillGraphicsObjectFactory::GetInstance(), "filled-landscape.svg");
        gm.CreateCircle("#facc15", 150, 100, 70);
        gm.CreateCircle("#ef4444", 150, 100, 45);
        gm.CreateRectangle("#22c55e", 40, 190, 220, 80);
        gm.CreateRectangle("#3b82f6", 75, 215, 150, 35);

        gm.WriteSVG();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Created blank-landscape.svg and filled-landscape.svg\n";
    return 0;
}
