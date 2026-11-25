#ifndef MEDIA_H
#define MEDIA_H
#include <cstddef>
#include <string>
#include "Object.h"

class Visitor;

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Abstract class for all kinds of media.
///
/// The class has a title and a duration. It is the base class of Song, Album and Collection.
class Media : public Object
{
public:
   /// @brief Constructor of a media.
   /// @param[in] title is the title of the media.
   /// @param[in] duration is the duration of the media.
   Media(std::string const& title, size_t const duration);

   /// @brief Returns a child of the media.
   /// @param[in] index is the position of the child.
   /// @returns the child at the given position or nullptr if there is none.
   ///
   /// A media without children returns nullptr.
   virtual Media const* GetChild(int const index) const;

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the media.
   ///
   /// Pure virtual method. Every concrete media calls the matching Visit method.
   virtual void Accept(Visitor& visitor) const = 0;

private:
   std::string mTitle;  ///< Title of the media.
   size_t mDuration;    ///< Duration of the media.
};
#endif //MEDIA_H
