#include "GraphicManagement.h"
#include "Image.h"
#include <stdexcept>

GraphicManagement::~GraphicManagement() = default;
GraphicManagement::GraphicManagement() = default;

void GraphicManagement::AddImage(const IGraphicObjectFactory &fact, const std::string &file) {
    mFactory = &fact;
    mImages.push_back(std::make_unique<Image>(file));
}

void GraphicManagement::WriteSVG() const {
    for (const auto &image : mImages) {
        image->WriteSVG();
    }
}

void GraphicManagement::CreateCircle(const std::string &stroke, int x, int y, size_t radius) {
    if (mFactory == nullptr) {
        throw std::logic_error("No factory is set.");
    }

    if (mImages.empty()) {
        throw std::logic_error("No image has been added.");
    }

    mImages.back()->AddGraphicObject(
        mFactory->CreateCircle(stroke, x, y, radius));
}

void GraphicManagement::CreateRectangle(const std::string &stroke, int x, int y, size_t width,
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
