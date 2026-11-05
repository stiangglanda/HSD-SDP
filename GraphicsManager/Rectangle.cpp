#include "Rectangle.h"

Rectangle::Rectangle(const std::string& stroke, int x, int y, size_t width, size_t height) :
	GraphicObject{stroke, x, y},
	mWidth{width},
	mHeight{height}
{
}

size_t Rectangle::GetWidth() const
{
	return mWidth;
}

size_t Rectangle::GetHeight() const
{
	return mHeight;
}
