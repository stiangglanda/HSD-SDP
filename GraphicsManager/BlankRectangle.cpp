#include "BlankRectangle.h"

BlankRectangle::BlankRectangle(const std::string& stroke, int x, int y, size_t width, size_t height) :
	Rectangle{stroke, x, y, width, height}
{
}

std::string BlankRectangle::ToSVG() const
{
	//<rect x="10" y="10" width="90" height="70" stroke="black" fill="none"/>
	std::string svg{};
	svg += "<rect x=\"";
	svg += std::to_string(GetX());
	svg += "\" y=\"";
	svg += std::to_string(GetY());
	svg += "\" width=\"";
	svg += std::to_string(GetWidth());
	svg += "\" height=\"";
	svg += std::to_string(GetHeight());
	svg += "\" stroke=\"";
	svg += GetStroke();
	svg += "\" fill=\"none\"/>";
	return svg;
}
