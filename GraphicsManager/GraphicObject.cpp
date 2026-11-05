#include "GraphicObject.h"

GraphicObject::GraphicObject(const std::string& stroke, int x, int y) :
	mStroke{stroke},
	mX{x},
	mY{y}
{
}

const std::string& GraphicObject::GetStroke() const
{
	return mStroke;
}

int GraphicObject::GetX() const
{
	return mX;
}

int GraphicObject::GetY() const
{
	return mY;
}
