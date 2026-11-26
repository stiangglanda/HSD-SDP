#ifndef SONG_H
#define SONG_H
#include <memory>

#include "Publication.h"
#include "Album.h"

/// @author Julian Rieger
/// @date 25.11.2026
/// @brief Concrete class for a song.
///
/// The class represents a song with its interpreter.
class Song : public Publication
{
public:
   /// @brief Constructor of a song.
   /// @param[in] title is the title of the song.
   /// @param[in] duration is the duration of the song.
   /// @param[in] interpreter is the name of the interpreter.
   ///
   /// Calls the constructor of a media.
   Song(std::string const& title, std::string const& interpreter, size_t const duration);

   /// @brief Returns the duration of the song.
   /// @returns the duration.
   ///
   /// Implements the pure virtual method of class Media.
   size_t GetDuration() const override;

   /// @brief Accepts a visitor.
   /// @param[in] visitor is the visitor that visits the song.
   ///
   /// Implements the pure virtual method of class Media.
   void Accept(Visitor& visitor) const override;

private:
   /// Only the constructor of Album may assign itself to a song.
   friend Album::Album(std::string const& title, std::string const& interpreter, std::vector<std::shared_ptr<Song>> songs);

   /// @brief Sets the album the song belongs to.
   /// @param[in] album is the album that contains the song.
   void SetAlbum(Album* album);

   Album* mAlbum = nullptr;  ///< Album of the song (0..1), not owned.

   size_t mDuration;  ///< Duration of the song.
};
#endif //SONG_H
