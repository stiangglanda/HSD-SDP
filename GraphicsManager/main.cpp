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
        std::cout << "Hello ";
        GraphicsManagement& gm = GraphicsManagement::GetInstance();
        gm.AddImage(BlankGraphicsObjectFactory::GetInstance(), "image1.svg");

        gm.CreateCircle("black", 50, 50, 25);
        gm.CreateRectangle("black", 100, 100, 50, 50);
        gm.AddImage(FillGraphicsObjectFactory::GetInstance(), "image2.svg");

        gm.WriteSVG();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Hello ";
    return 0;
}
