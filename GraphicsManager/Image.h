#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <string>
#include <vector>
#include "GraphicObject.h"
#include "Object.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief An image which consists of graphical objects and is stored as SVG file.
///
/// The graphical objects are defined in the private method Init, which is
/// called by the constructor. They are created with the factory that is
/// currently set in the GraphicsManagement, so an image contains only filled
/// or only not filled objects.
class Image : public Object
{
public:
   /// @brief Creates an image and its graphical objects.
   /// @param[in] filename is the name of the SVG file.
   explicit Image(const std::string& filename);

   /// @brief Writes the image as SVG file.
   /// @throws std::runtime_error if the file can not be opened.
   void WriteSVG() const;

private:
   /// @brief Defines the graphical objects of the image.
   void Init();

   /// @brief Name of the SVG file.
   std::string mFilename;

   /// @brief All graphical objects of the image, owned by the image.
   std::vector<std::unique_ptr<GraphicObject>> mGraphicObjects;
};

#endif
