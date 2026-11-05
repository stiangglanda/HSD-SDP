#include "BlankCircle.h"

std::string BlankCircle::ToSVG() const
{
	//<circle cx="55" cy="45" r="35" stroke="black" fill="none"/>
	std::string svg{};
	svg += "<circle cx=";
	svg += std::to_string(GetX());
	svg += "\" cy=\"";
	svg += std::to_string(GetY());
	svg += "\" r=\"";
	svg += std::to_string(GetRadius());
	svg += "\" stroke=\"";
	svg += GetStroke();
	svg += "\" fill=\"none\"/>";
	return svg;
}

BlankCircle::BlankCircle(const std::string& stroke, int x, int y, size_t radius) :
	Circle{stroke, x, y, radius}
{
}