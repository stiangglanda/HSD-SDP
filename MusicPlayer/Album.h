#ifndef ALBUM_H
#define ALBUM_H
#include <vector>
#include "Media.h"

class Song;

/// @author Leander
/// @date 25.11.2026
/// @brief Concrete class for an album.
///
/// The class represents an album and aggregates at least one song.
class Album : public Media
{
public:
   /// @brief Constructor of an album.
   /// @param[in] title is the title of the album.
   /// @param[in] duration is the duration of the album.
   ///
   /// Calls the constructor of a media.
   Album(std::string const& title, size_t const duration);

   /// @brief Returns the number of songs.
   /// @returns the number of songs of the album.
   size_t GetNumSongs() const;

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
   std::vector<Song*> mSongs;  ///< Songs of the album (1..*).
};
#endif //ALBUM_H
