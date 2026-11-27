#ifndef ICOLLECTION_H
#define ICOLLECTION_H

#include <memory>
#include <string>

class Media;

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Interface for a collection of media.
///
/// The interface defines how media is added to and removed from a collection.
class ICollection
{
public:
   /// @brief Virtual destructor of the interface.
   virtual ~ICollection() = default;

   /// @brief Adds a media to the collection.
   /// @param[in] media is the media to add.
   /// @throws std::invalid_argument if the media is a null pointer or would create a cycle.
   virtual void Add(std::shared_ptr<Media> media) = 0;

   /// @brief Removes a media from the collection.
   /// @param[in] title is the title of the media to remove.
   /// @returns true if a media was removed, otherwise false.
   virtual bool Remove(std::string const& title) = 0;
};
#endif //ICOLLECTION_H
