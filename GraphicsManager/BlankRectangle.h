#ifndef BLANKRECTANGLE_H
#define BLANKRECTANGLE_H
#include <cstddef>
#include <string>
#include "Rectangle.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief A not filled rectangle.
///
/// Objects of this class can only be created by the BlankGraphicsObjectFactory.
class BlankRectangle : public Rectangle
{
public:
   /// @brief Creates the SVG element of this not filled rectangle.
   /// @returns the SVG element as text.
   std::string ToSVG() const override;

private:
   /// @brief Only the factory is allowed to create objects.
   friend class BlankGraphicsObjectFactory;

   /// @brief Creates the object.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate.
   /// @param[in] y is the y coordinate.
   /// @param[in] width is the width of the rectangle.
   /// @param[in] height is the height of the rectangle.
   BlankRectangle(const std::string& stroke, int x, int y, size_t width, size_t height);
};

#endif
