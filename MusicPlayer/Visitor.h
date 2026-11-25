#ifndef VISITOR_H
#define VISITOR_H

class Collection;
class Song;
class Album;

/// @author Leander
/// @date 25.11.2026
/// @brief Interface for a visitor of media.
///
/// The interface has one Visit method for each concrete type of media.
class Visitor
{
public:
   /// @brief Virtual destructor of the interface.
   virtual ~Visitor() = default;

   /// @brief Visits a collection.
   /// @param[in] collection is the collection to visit.
   virtual void Visit(Collection const& collection) = 0;

   /// @brief Visits a song.
   /// @param[in] song is the song to visit.
   virtual void Visit(Song const& song) = 0;

   /// @brief Visits an album.
   /// @param[in] album is the album to visit.
   virtual void Visit(Album const& album) = 0;
};
#endif //VISITOR_H
