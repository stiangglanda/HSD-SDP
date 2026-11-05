#ifndef FILLEDRECTANGLE_H
#define FILLEDRECTANGLE_H
#include <cstddef>
#include <string>
#include "Rectangle.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief A filled rectangle.
///
/// Objects of this class can only be created by the FillGraphicsObjectFactory.
class FilledRectangle : public Rectangle
{
public:
   /// @brief Creates the SVG element of this filled rectangle.
   /// @returns the SVG element as text.
   std::string ToSVG() const override;

   /// @brief Creates the object.
   /// @param[in] stroke is the color of the outline (and of the fill).
   /// @param[in] x is the x coordinate.
   /// @param[in] y is the y coordinate.
   /// @param[in] width is the width of the rectangle.
   /// @param[in] height is the height of the rectangle.
   FilledRectangle(const std::string& stroke, int x, int y, size_t width, size_t height);
};

#endif
