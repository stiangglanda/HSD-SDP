#ifndef VISITORSEARCH_H
#define VISITORSEARCH_H
#include "Visitor.h"

/// @author Leander
/// @date 25.11.2026
/// @brief Concrete visitor that searches for media.
///
/// The class implements all Visit methods of the interface Visitor.
class VisitorSearch : public Visitor
{
public:
   /// @brief Visits a collection and searches in it.
   /// @param[in] collection is the collection to visit.
   void Visit(Collection const& collection) override;

   /// @brief Visits a song and checks if it matches the search.
   /// @param[in] song is the song to visit.
   void Visit(Song const& song) override;

   /// @brief Visits an album and searches in it.
   /// @param[in] album is the album to visit.
   void Visit(Album const& album) override;
};
#endif //VISITORSEARCH_H
