#ifndef VISITORPLAY_H
#define VISITORPLAY_H
#include "Visitor.h"

/// @author Leander
/// @date 25.11.2026
/// @brief Concrete visitor that plays media.
///
/// The class implements all Visit methods of the interface Visitor.
class VisitorPlay : public Visitor
{
public:
   /// @brief Visits a collection and plays all of its media.
   /// @param[in] collection is the collection to visit.
   void Visit(Collection const& collection) override;

   /// @brief Visits a song and plays it.
   /// @param[in] song is the song to visit.
   void Visit(Song const& song) override;

   /// @brief Visits an album and plays all of its songs.
   /// @param[in] album is the album to visit.
   void Visit(Album const& album) override;
};
#endif //VISITORPLAY_H
