#include "GraphicsManagement.h"

void GraphicsManagement::AddImage(const IGraphicsObjectFactory &fact, const std::string &file) {
    mFactory = &fact;
}

void GraphicsManagement::WriteSVG() const {
}

std::unique_ptr<Circle> GraphicsManagement::CreateCircle(const std::string &stroke, int x, int y, size_t radius) const {
    return mFactory->CreateCircle(stroke, x, y, radius);
}

std::unique_ptr<Rectangle> GraphicsManagement::CreateRectangle(const std::string &stroke, int x, int y, size_t width,
    size_t height) const {
    return mFactory->CreateRectangle(stroke, x, y, width, height);
}
