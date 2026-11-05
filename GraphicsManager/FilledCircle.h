#ifndef FILLEDCIRCLE_H
#define FILLEDCIRCLE_H
#include <cstddef>
#include <string>
#include "Circle.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief A filled circle.
///
/// Objects of this class can only be created by the FillGraphicsObjectFactory.
class FilledCircle : public Circle
{
public:
   /// @brief Creates the SVG element of this filled circle.
   /// @returns the SVG element as text.
   std::string ToSVG() const override;

private:
   /// @brief Only the factory is allowed to create objects.
   friend class FillGraphicsObjectFactory;

   /// @brief Creates the object.
   /// @param[in] stroke is the color of the outline (and of the fill).
   /// @param[in] x is the x coordinate.
   /// @param[in] y is the y coordinate.
   /// @param[in] radius is the radius of the circle.
   FilledCircle(const std::string& stroke, int x, int y, size_t radius);
};

#endif
