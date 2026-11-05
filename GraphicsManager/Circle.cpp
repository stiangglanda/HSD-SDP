#include "Circle.h"
#include <stdexcept>

Circle::Circle(const std::string& stroke, int x, int y, size_t radius) :
	GraphicObject{stroke, x, y},
	mRadius{radius}
{
	if (radius == 0) {
		throw std::invalid_argument("Radius must not be 0");
	}
}

size_t Circle::GetRadius() const
{
	return mRadius;
}
