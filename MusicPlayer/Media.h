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
/// The class has a title. The duration is stored by a song and calculated by album and collection.
/// It is the base class of Publication and Collection.
class Media : public Object
{
public:
   /// @brief Constructor of a media.
   /// @param[in] title is the title of the media.
   /// @throws std::invalid_argument if the title is empty.
   explicit Media(std::string const& title);

   /// @brief Returns the title of the media.
   /// @returns the title.
   std::string const& GetTitle() const;

   /// @brief Returns the duration of the media in seconds.
   /// @returns the duration.
   virtual size_t GetDuration() const = 0;

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

protected:
   /// @brief Adds two durations.
   /// @param[in] a is the first duration.
   /// @param[in] b is the second duration.
   /// @returns the sum of both durations.
   /// @throws std::overflow_error if the sum does not fit into size_t.
   static size_t AddDuration(size_t const a, size_t const b);

private:
   std::string mTitle;  ///< Title of the media.
};
#endif //MEDIA_H
