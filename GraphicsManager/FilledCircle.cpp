#include "FilledCircle.h"

FilledCircle::FilledCircle(const std::string& stroke, int x, int y, size_t radius)
	: Circle(stroke, x, y, radius)
{
}

std::string FilledCircle::ToSVG() const
{
	//<circle cx="55" cy="45" r="35" stroke="black"/>
	std::string svg{};
	svg += "<circle cx=\"";
	svg += std::to_string(GetX());
	svg += "\" cy=\"";
	svg += std::to_string(GetY());
	svg += "\" r=\"";
	svg += std::to_string(GetRadius());
	svg += "\" stroke=\"";
	svg += GetStroke();
	svg += "\"/>";
	return svg;
}
