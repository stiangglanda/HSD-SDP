#include "Image.h"

Image::Image(const std::string& filename) :
	mFilename{filename}
{

}

void Image::WriteSVG() const
{

}

void Image::AddGraphicObect(std::unique_ptr<GraphicObject> obj)
{
	mGraphicObjects.push_back(obj);
}
