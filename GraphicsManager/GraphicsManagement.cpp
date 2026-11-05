#include "GraphicsManagement.h"
#include "Image.h"
#include <stdexcept>

GraphicsManagement::~GraphicsManagement() = default;
GraphicsManagement::GraphicsManagement() = default;

void GraphicsManagement::AddImage(const IGraphicsObjectFactory &fact, const std::string &file) {
    mFactory = &fact;
    mImages.push_back(std::make_unique<Image>(file));
}

void GraphicsManagement::WriteSVG() const {
    for (const auto &image : mImages) {
        image->WriteSVG();
    }
}

void GraphicsManagement::CreateCircle(const std::string &stroke, int x, int y, size_t radius) {
    if (mFactory == nullptr) {
        throw std::logic_error("No factory is set.");
    }

    if (mImages.empty()) {
        throw std::logic_error("No image has been added.");
    }

    mImages.back()->AddGraphicObject(
        mFactory->CreateCircle(stroke, x, y, radius));
}

void GraphicsManagement::CreateRectangle(const std::string &stroke, int x, int y, size_t width,
                                        size_t height) {
    if (mFactory == nullptr) {
        throw std::logic_error("No factory is set.");
    }

    if (mImages.empty()) {
        throw std::logic_error("No image has been added.");
    }

    mImages.back()->AddGraphicObject(
        mFactory->CreateRectangle(stroke, x, y, width, height));
}
