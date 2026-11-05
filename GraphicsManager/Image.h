#ifndef IMAGE_H
#define IMAGE_H
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include "GraphicObject.h"
#include "Object.h"

/// @author Julian Rieger
/// @date 05.11.2026
/// @brief An image which consists of graphical objects and is stored as SVG file.
///
class Image : public Object
{
public:
	/// @brief Creates an image and its graphical objects.
	/// @param[in] filename is the name of the SVG file.
	explicit Image(const std::string& filename);

	/// @brief Writes the image as SVG file.
	/// @throws std::runtime_error if the file can not be opened.
	void WriteSVG() const;

	/// @brief Adds a graphic object to the vector.
	/// Uses push_back() internally.
	void AddGraphicObject(std::unique_ptr<GraphicObject> obj);

private:

	/// @brief Name of the SVG file.
	std::string mFilename;

	/// @brief All graphical objects of the image, owned by the image.
	std::vector<std::unique_ptr<GraphicObject>> mGraphicObjects;

	///	@brief Prints the formated header of the SVG file
	void PrintHeader(std::ostream& ost) const;

	///	@brief Prints the formated footer of the SVG file
	void PrintFooter(std::ostream& ost) const;

};

#endif