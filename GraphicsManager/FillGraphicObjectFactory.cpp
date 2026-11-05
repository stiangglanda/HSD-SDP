#include "FillGraphicObjectFactory.h"
#include "FillCircle.h"
#include "FillRectangle.h"

std::unique_ptr<Circle> FillGraphicObjectFactory::CreateCircle(const std::string &stroke, int x, int y,
                                                                size_t radius) const {
    return std::make_unique<FillCircle>(stroke, x, y, radius);
}

std::unique_ptr<Rectangle> FillGraphicObjectFactory::CreateRectangle(const std::string &stroke, int x, int y,
    size_t width, size_t height) const {
    return std::make_unique<FillRectangle>(stroke, x, y, width, height);
}