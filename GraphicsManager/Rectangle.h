#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <cstddef>
#include <string>
#include "GraphicObject.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief Abstract base class of all rectangles.
///
/// The position (mX, mY) is the upper left corner of the rectangle. Whether
/// the rectangle is filled or not is decided by the derived classes in ToSVG.
class Rectangle : public GraphicObject
{
public:
   /// @brief Creates the SVG element of the rectangle, implemented by the derived classes.
   /// @returns the SVG element as text.
   std::string ToSVG() const override = 0;

protected:
   /// @brief Creates a rectangle.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the upper left corner.
   /// @param[in] y is the y coordinate of the upper left corner.
   /// @param[in] width is the width of the rectangle.
   /// @param[in] height is the height of the rectangle.
   Rectangle(const std::string& stroke, int x, int y, size_t width, size_t height);

   /// @brief Access function for the width.
   /// @returns the width.
   size_t GetWidth() const;

   /// @brief Access function for the height.
   /// @returns the height.
   size_t GetHeight() const;

private:
   /// @brief Width of the rectangle.
   size_t mWidth;

   /// @brief Height of the rectangle.
   size_t mHeight;
};

#endif
