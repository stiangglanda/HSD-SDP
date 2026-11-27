#ifndef ALBUM_H
#define ALBUM_H
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "Publication.h"

class Song;

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Concrete class for an album.
///
/// The class represents an album and aggregates at least one song.
class Album : public Publication
{
public:
   /// @brief Constructor of an album.
   /// @param[in] title is the title of the album.
   /// @param[in] interpreter is the interpreter of the album.
   /// @param[in] songs are the songs of the album.
   /// @throws std::invalid_argument if the title or the interpreter is empty,
   ///         if there are no songs or if a song is a null pointer.
   Album(std::string const& title, std::string const& interpreter, std::vector<std::shared_ptr<Song>> songs);

   /// @brief Returns the number of songs.
   /// @returns the number of songs of the album.
   size_t GetNumSongs() const;

   /// @brief Returns the duration of the album.
   /// @returns the sum of the durations of all songs.
   /// @throws std::overflow_error if the sum does not fit into size_t.
   ///
   /// Implements the pure virtual method of class Media.
   size_t GetDuration() const override;

   /// @brief Returns a song of the album.
   /// @param[in] index is the position of the song.
   /// @returns the song at the given position or nullptr if there is none.
   ///
   /// Overrides the method of class Media.
   Media const* GetChild(int const index) const override;

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the album.
   ///
   /// Implements the pure virtual method of class Media.
   void Accept(Visitor& visitor) const override;

private:
   std::vector<std::shared_ptr<Song>> mSongs;  ///< Songs of the album (1..*).
};
#endif //ALBUM_H
