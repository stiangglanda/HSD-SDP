#ifndef VISITORSEARCH_H
#define VISITORSEARCH_H
#include <string>

#include "Object.h"
#include "Visitor.h"

/// @author Leander Kieweg
/// @date 25.11.2026
/// @brief Concrete visitor that searches for media.
///
/// The class prints every media whose title contains the search term to std::cout.
class VisitorSearch : public Object, public Visitor
{
public:
   /// @brief Constructor.
   /// @param[in] searchTerm is the term to search for.
   /// @throws std::invalid_argument if the search term is empty.
   explicit VisitorSearch(std::string const& searchTerm);

   /// @brief Visits a collection and searches in it.
   /// @param[in] collection is the collection to visit.
   void Visit(Collection const& collection) override;

   /// @brief Visits a song and checks if it matches the search.
   /// @param[in] song is the song to visit.
   void Visit(Song const& song) override;

   /// @brief Visits an album and searches in it.
   /// @param[in] album is the album to visit.
   void Visit(Album const& album) override;

private:
   /// @brief Prints the title if it contains the search term.
   /// @param[in] title is the title to check.
   void Check(std::string const& title) const;

   std::string mSearchTerm;  ///< Term to search for.
};
#endif //VISITORSEARCH_H
