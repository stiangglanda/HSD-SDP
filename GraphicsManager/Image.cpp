#include "Image.h"
#include <fstream>
#include <stdexcept>
#include <utility>

Image::Image(const std::string& filename) :
    mFilename{ filename }
{
}

void Image::WriteSVG() const
{
    std::ofstream file(mFilename);
    if (!file.is_open())
        throw std::runtime_error("Error: Can not open file " + mFilename);

    PrintHeader(file);
    for (const auto& elem : mGraphicObjects)
        file << elem->ToSVG() << "\n";
    PrintFooter(file);

    file.close();
}

void Image::AddGraphicObject(std::unique_ptr<GraphicObject> obj)
{
    mGraphicObjects.push_back(std::move(obj));
}

void Image::PrintHeader(std::ostream& out) const
{
    out << "<?xml version=\"1.0\"?>\n"
        << "<svg xmlns=\"http://www.w3.org/2000/svg\">\n";
}

void Image::PrintFooter(std::ostream& out) const
{
    out << "</svg>\n";
}