#ifndef GRAPHICMANAGEMENT_H
#define GRAPHICMANAGEMENT_H
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "Circle.h"
#include "IGraphicObjectFactory.h"
#include "Object.h"
#include "Rectangle.h"
#include "SingletonBase.h"

class Image;

/// @author Leander Kieweg
/// @date 05.11.2026
/// @brief Manages all images (singleton).
///
/// The management exists only once and is released automatically when the
/// program ends. The factory that creates the graphical objects can be
/// exchanged: each call of AddImage sets the factory for the new image.
class GraphicManagement : public SingletonBase<GraphicManagement>
{
   friend class SingletonBase<GraphicManagement>;
public:
   ~GraphicManagement() override;

   /// @brief Creates a new image with the given factory and stores it.
   /// @param[in] fact is the factory used for all objects of the new image.
   /// @param[in] file is the name of the SVG file of the image.
   void AddImage(const IGraphicObjectFactory& fact, const std::string& file);

   /// @brief Writes all images as SVG files.
   /// @throws std::runtime_error if a file can not be opened.
   void WriteSVG() const;

   /// @brief Creates a circle with the current factory.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the center.
   /// @param[in] y is the y coordinate of the center.
   /// @param[in] radius is the radius of the circle.
   /// @returns the created circle, the caller owns it.
   /// @throws std::logic_error if no factory is set.
   void CreateCircle(const std::string& stroke, int x, int y, size_t radius);

   /// @brief Creates a rectangle with the current factory.
   /// @param[in] stroke is the color of the outline.
   /// @param[in] x is the x coordinate of the upper left corner.
   /// @param[in] y is the y coordinate of the upper left corner.
   /// @param[in] width is the width of the rectangle.
   /// @param[in] height is the height of the rectangle.
   /// @returns the created rectangle, the caller owns it.
   /// @throws std::logic_error if no factory is set.
   void CreateRectangle(const std::string& stroke, int x, int y, size_t width, size_t height);

private:
   /// @brief Private constructor, use GetInstance.
   GraphicManagement();

   /// @brief Factory for the next images, not owned (the factories are singletons).
   const IGraphicObjectFactory* mFactory = nullptr;

   /// @brief All images, owned by the management.
   std::vector<std::unique_ptr<Image>> mImages;
};

#endif
