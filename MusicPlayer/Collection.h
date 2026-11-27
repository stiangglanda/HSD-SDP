#ifndef COLLECTION_H
#define COLLECTION_H
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "Media.h"
#include "ICollection.h"

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Concrete class for a collection of media.
///
/// The class aggregates any number of media and implements the interface ICollection.
/// Collections can be nested, but a collection must never contain itself.
class Collection : public Media, public ICollection
{
public:
   /// @brief Constructor of a collection.
   /// @param[in] title is the title of the collection.
   /// @throws std::invalid_argument if the title is empty.
   explicit Collection(std::string const& title);

   /// @brief Adds a media to the collection.
   /// @param[in] media is the media to add.
   /// @throws std::invalid_argument if the media is a null pointer, the collection itself
   ///         or a collection that already contains this collection (cycle).
   ///
   /// Implements the pure virtual method of interface ICollection.
   void Add(std::shared_ptr<Media> media) override;

   /// @brief Removes a media from the collection.
   /// @param[in] title is the title of the media to remove.
   /// @returns true if a media was removed, otherwise false.
   ///
   /// Removes the first media with the given title. Nested collections are searched as well.
   /// Implements the pure virtual method of interface ICollection.
   bool Remove(std::string const& title) override;

   /// @brief Returns a media of the collection.
   /// @param[in] index is the position of the media.
   /// @returns the media at the given position or nullptr if there is none.
   ///
   /// Overrides the method of class Media.
   Media const* GetChild(int const index) const override;

   /// @brief Returns the number of songs.
   /// @returns the number of songs of the collection, including songs in albums and nested collections.
   size_t GetNumSongs() const;

   /// @brief Returns the duration of the collection.
   /// @returns the sum of the durations of all media.
   /// @throws std::overflow_error if the sum does not fit into size_t.
   ///
   /// Implements the pure virtual method of class Media.
   size_t GetDuration() const override;

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the collection.
   ///
   /// Implements the pure virtual method of class Media.
   void Accept(Visitor& visitor) const override;

private:
   std::vector<std::shared_ptr<Media>> mMedias;  ///< Media of the collection (*).
};
#endif //COLLECTION_H
