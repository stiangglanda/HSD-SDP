#ifndef BLANKCIRCLE_H
#define BLANKCIRCLE_H
#include <cstddef>
#include <string>
#include "Circle.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief A not filled circle.
///
/// Objects of this class can only be created by the BlankGraphicsObjectFactory.
class BlankCircle : public Circle
{
public:
   /// @brief Creates the SVG element of this not filled circle.
   /// @returns the SVG element as text.
   std::string ToSVG() const override;

   /// @brief Creates the object.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate.
   /// @param[in] y is the y coordinate.
   /// @param[in] radius is the radius of the circle.
   BlankCircle(const std::string& stroke, int x, int y, size_t radius);
};

#endif
