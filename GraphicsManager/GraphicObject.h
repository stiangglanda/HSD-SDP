#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H
#include <string>
#include "Object.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief Abstract base class of all graphical objects.
///
/// A graphical object has a stroke color and a position. How the object is
/// described in a SVG file is defined by the derived classes.
class GraphicObject : public Object
{
public:
   /// @brief Creates the SVG element which describes this object.
   /// @returns the SVG element as text (one line, without line break).
   virtual std::string ToSVG() const = 0;

protected:
   /// @brief Creates a graphical object.
   /// @param[in] stroke is the color of the outline (e.g. "black").
   /// @param[in] x is the x coordinate of the object.
   /// @param[in] y is the y coordinate of the object.
   GraphicObject(const std::string& stroke, int x, int y);

   /// @brief Access function for the stroke color.
   /// @returns the stroke color.
   const std::string& GetStroke() const;

   /// @brief Access function for the x coordinate.
   /// @returns the x coordinate.
   int GetX() const;

   /// @brief Access function for the y coordinate.
   /// @returns the y coordinate.
   int GetY() const;

private:
   /// @brief Color of the outline.
   std::string mStroke;

   /// @brief x coordinate (center of a circle, upper left corner of a rectangle).
   int mX;

   /// @brief y coordinate (center of a circle, upper left corner of a rectangle).
   int mY;
};

#endif
