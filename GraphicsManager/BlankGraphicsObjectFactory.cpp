#include "BlankGraphicsObjectFactory.h"

#include "BlankCircle.h"

std::unique_ptr<Circle> BlankGraphicsObjectFactory::CreateCircle(const std::string &stroke, int x, int y,
                                                                 size_t radius) const {
    return std::make_unique<BlankCircle>(stroke, x, y, radius);
}

std::unique_ptr<Rectangle> BlankGraphicsObjectFactory::CreateRectangle(const std::string &stroke, int x, int y,
    size_t width, size_t height) const {
    return GraphicsObjectFactory::CreateRectangle(stroke, x, y, width, height);
}