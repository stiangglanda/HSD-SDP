#include "FillGraphicsObjectFactory.h"
#include "FilledCircle.h"
#include "FilledRectangle.h"

std::unique_ptr<Circle> FillGraphicsObjectFactory::CreateCircle(const std::string &stroke, int x, int y,
                                                                 size_t radius) const {
    return std::make_unique<FilledCircle>(stroke, x, y, radius);
}

std::unique_ptr<Rectangle> FillGraphicsObjectFactory::CreateRectangle(const std::string &stroke, int x, int y,
    size_t width, size_t height) const {
    return std::make_unique<FilledRectangle>(stroke, x, y, width, height);
}