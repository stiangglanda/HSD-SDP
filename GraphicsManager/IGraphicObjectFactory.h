#ifndef IGRAPHICSOBJECTFACTORY_H
#define IGRAPHICSOBJECTFACTORY_H
#include <cstddef>
#include <memory>
#include <string>
#include "Circle.h"
#include "Rectangle.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief Interface of the abstract factory which creates graphical objects.
///
/// Every concrete factory creates a family of objects (e.g. only filled or
/// only not filled ones). New families (hatched, dotted, ...) can be added by
/// implementing this interface, without changing the existing classes.
class IGraphicObjectFactory
{
public:
   /// @brief Virtual destructor.
   virtual ~IGraphicObjectFactory() = default;

   /// @brief Creates a circle.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the center.
   /// @param[in] y is the y coordinate of the center.
   /// @param[in] radius is the radius of the circle.
   /// @returns the created circle, the caller owns it.
   virtual std::unique_ptr<Circle> CreateCircle(const std::string& stroke, int x, int y, size_t radius) const = 0;

   /// @brief Creates a rectangle.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the upper left corner.
   /// @param[in] y is the y coordinate of the upper left corner.
   /// @param[in] width is the width of the rectangle.
   /// @param[in] height is the height of the rectangle.
   /// @returns the created rectangle, the caller owns it.
   virtual std::unique_ptr<Rectangle> CreateRectangle(const std::string& stroke, int x, int y, size_t width, size_t height) const = 0;
};

#endif
