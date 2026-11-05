#ifndef FILLGRAPHICSOBJECTFACTORY_H
#define FILLGRAPHICSOBJECTFACTORY_H
#include <cstddef>
#include <memory>
#include <string>
#include "IGraphicsObjectFactory.h"
#include "Object.h"
#include "SingletonBase.h"

/// @author Leander Kieweg
/// @date 05.11.2026
/// @brief Factory which creates filled circles and rectangles.
///
/// The factory exists only once (singleton). It is created at the first call
/// of GetInstance and released automatically when the program ends.
class FillGraphicsObjectFactory : public IGraphicsObjectFactory, public SingletonBase<FillGraphicsObjectFactory>
{
   friend class SingletonBase<FillGraphicsObjectFactory>;
public:

   /// @brief Creates a filled circle.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the center.
   /// @param[in] y is the y coordinate of the center.
   /// @param[in] radius is the radius of the circle.
   /// @returns the created circle, the caller owns it.
   std::unique_ptr<Circle> CreateCircle(const std::string& stroke, int x, int y, size_t radius) const override;

   /// @brief Creates a filled rectangle.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the upper left corner.
   /// @param[in] y is the y coordinate of the upper left corner.
   /// @param[in] width is the width of the rectangle.
   /// @param[in] height is the height of the rectangle.
   /// @returns the created rectangle, the caller owns it.
   std::unique_ptr<Rectangle> CreateRectangle(const std::string& stroke, int x, int y, size_t width, size_t height) const override;

private:
   /// @brief Private constructor, use GetInstance.
   FillGraphicsObjectFactory() = default;
};

#endif
