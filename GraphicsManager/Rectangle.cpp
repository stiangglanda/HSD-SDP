#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const std::string& stroke, int x, int y, size_t width, size_t height) :
	GraphicObject{stroke, x, y},
	mWidth{width},
	mHeight{height}
{
	if (width == 0 || height == 0) {
		throw std::invalid_argument("Width and height must not be 0");
	}
}

size_t Rectangle::GetWidth() const
{
	return mWidth;
}

size_t Rectangle::GetHeight() const
{
	return mHeight;
}
