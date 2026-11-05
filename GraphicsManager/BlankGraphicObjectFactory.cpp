#include "BlankGraphicObjectFactory.h"
#include "BlankCircle.h"
#include "BlankRectangle.h"

std::unique_ptr<Circle> BlankGraphicObjectFactory::CreateCircle(const std::string &stroke, int x, int y,
                                                                 size_t radius) const {
    return std::make_unique<BlankCircle>(stroke, x, y, radius);
}

std::unique_ptr<Rectangle> BlankGraphicObjectFactory::CreateRectangle(const std::string &stroke, int x, int y,
    size_t width, size_t height) const {
    return std::make_unique<BlankRectangle>(stroke, x, y, width, height);
}