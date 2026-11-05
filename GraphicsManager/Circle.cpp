#include "Circle.h"

Circle::Circle(const std::string& stroke, int x, int y, size_t radius) :
	GraphicObject{stroke, x, y},
	mRadius{radius}
{
}

size_t Circle::GetRadius() const
{
	return mRadius;
}
