#ifndef VISITORPLAY_H
#define VISITORPLAY_H
#include <cstddef>
#include <string>

#include "Object.h"
#include "Visitor.h"

/// @author Leander Kieweg
/// @date 25.11.2026
/// @brief Concrete visitor that plays media.
///
/// The class prints all media hierarchically to std::cout.
/// Contained media are indented, songs are numbered consecutively.
class VisitorPlay : public Object, public Visitor
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

private:
   /// @brief Formats a duration as mm:ss.
   /// @param[in] seconds is the duration in seconds.
   /// @returns the formatted duration.
   static std::string FormatDuration(size_t const seconds);

   /// @brief Returns the indentation for the current level.
   /// @returns a string of spaces.
   std::string Indent() const;

   size_t mSongCounter = 0;  ///< Number of songs played so far.
   size_t mLevel = 0;        ///< Current nesting level.
};
#endif //VISITORPLAY_H
