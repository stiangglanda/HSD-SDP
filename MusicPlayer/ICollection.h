#ifndef ICOLLECTION_H
#define ICOLLECTION_H

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
   virtual void Add(Media* media) = 0;

   /// @brief Removes a media from the collection.
   /// @param[in] media is the media to remove.
   virtual void Remove(Media* media) = 0;
};
#endif //ICOLLECTION_H
