#ifndef CIRCLE_H
#define CIRCLE_H
#include <cstddef>
#include <string>
#include "GraphicObject.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief Abstract base class of all circles.
///
/// The position (mX, mY) is the center of the circle. Whether the circle is
/// filled or not is decided by the derived classes in ToSVG.
class Circle : public GraphicObject
{
public:
   /// @brief Creates the SVG element of the circle, implemented by the derived classes.
   /// @returns the SVG element as text.
   std::string ToSVG() const override = 0;

protected:
   /// @brief Creates a circle.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the center.
   /// @param[in] y is the y coordinate of the center.
   /// @param[in] radius is the radius of the circle.
   Circle(const std::string& stroke, int x, int y, size_t radius);

   /// @brief Access function for the radius.
   /// @returns the radius.
   size_t GetRadius() const;

private:
   /// @brief Radius of the circle.
   size_t mRadius;
};

#endif
