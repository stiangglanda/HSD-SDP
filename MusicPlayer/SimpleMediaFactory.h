#ifndef SIMPLEMEDIAFACTORY_H
#define SIMPLEMEDIAFACTORY_H
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "Object.h"

class Album;
class Collection;
class Song;

/// @author Leander Kieweg
/// @date 25.11.2026
/// @brief Factory that creates media.
///
/// The class creates songs, albums and collections, so the client does not
/// need to know the constructors of the concrete classes.
class SimpleMediaFactory : public Object
{
public:
   /// @brief Creates a song.
   /// @param[in] title is the title of the song.
   /// @param[in] interpreter is the name of the interpreter.
   /// @param[in] duration is the duration of the song in seconds.
   /// @returns the new song.
   /// @throws std::invalid_argument if the title or the interpreter is empty.
   std::shared_ptr<Song> CreateSong(std::string const& title,
                                    std::string const& interpreter,
                                    size_t const duration) const;

   /// @brief Creates an album.
   /// @param[in] title is the title of the album.
   /// @param[in] interpreter is the name of the interpreter.
   /// @param[in] songs are the songs of the album.
   /// @returns the new album.
   /// @throws std::invalid_argument if the title or the interpreter is empty,
   ///         if there are no songs or if a song is a null pointer.
   std::shared_ptr<Album> CreateAlbum(std::string const& title,
                                      std::string const& interpreter,
                                      std::vector<std::shared_ptr<Song>> songs) const;

   /// @brief Creates an empty collection.
   /// @param[in] title is the title of the collection.
   /// @returns the new collection.
   /// @throws std::invalid_argument if the title is empty.
   std::shared_ptr<Collection> CreateCollection(std::string const& title) const;
};
#endif //SIMPLEMEDIAFACTORY_H
