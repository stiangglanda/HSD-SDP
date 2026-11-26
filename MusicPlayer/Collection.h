#ifndef COLLECTION_H
#define COLLECTION_H
#include <vector>
#include "Media.h"
#include "ICollection.h"

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Concrete class for a collection of media.
///
/// The class aggregates any number of media and implements the interface ICollection.
class Collection : public Media, public ICollection
{
public:
   /// @brief Constructor of a collection.
   /// @param[in] title is the title of the collection.
   ///
   /// Calls the constructor of a media.
   Collection(std::string const& title);

   /// @brief Plays all media of the collection.
   void Play();

   /// @brief Adds a media to the collection.
   /// @param[in] media is the media to add.
   ///
   /// Implements the pure virtual method of interface ICollection.
   void Add(Media* media) override;

   /// @brief Removes a media from the collection.
   /// @param[in] media is the media to remove.
   ///
   /// Implements the pure virtual method of interface ICollection.
   void Remove(Media* media) override;

   /// @brief Returns a media of the collection.
   /// @param[in] index is the position of the media.
   /// @returns the media at the given position or nullptr if there is none.
   ///
   /// Overrides the method of class Media.
   Media const* GetChild(int const index) const override;

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the collection.
   ///
   /// Implements the pure virtual method of class Media.
   void Accept(Visitor& visitor) const override;

private:
   std::vector<Media*> mMedias;  ///< Media of the collection (*).
};
#endif //COLLECTION_H
