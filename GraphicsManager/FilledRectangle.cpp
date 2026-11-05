#include "FilledRectangle.h"

FilledRectangle::FilledRectangle(const std::string& stroke, int x, int y, size_t width, size_t height) :
	Rectangle{stroke, x, y, width, height}
{
}

std::string FilledRectangle::ToSVG() const
{
	//<rect x="10" y="10" width="90" height="70" stroke="black"/>
	std::string svg{};
	svg += "<rect x=";
	svg += std::to_string(GetX());
	svg += "\" y=\"";
	svg += std::to_string(GetY());
	svg += "\" width=\"";
	svg += std::to_string(GetWidth());
	svg += "\" height=\"";
	svg += std::to_string(GetHeight());
	svg += "\" stroke=\"";
	svg += GetStroke();
	svg += "\"/>";
	return svg;
}
