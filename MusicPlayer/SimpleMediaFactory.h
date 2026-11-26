#ifndef SIMPLEMEDIAFACTORY_H
#define SIMPLEMEDIAFACTORY_H
#include <memory>
#include <string>
#include <vector>
#include "Song.h"

class Collection;
class Media;

/// @author Leander Kieweg
/// @date 25.11.2026
/// @brief Factory that creates media.
///
/// The class creates a song, an album or a collection depending on the kind.
class SimpleMediaFactory
{
public:
   /// @brief Creates a media.
   /// @param[in] kind is the kind of media, for example "song", "album" or "collection".
   /// @returns a new media of the given kind or nullptr if the kind is unknown.
   ///
   /// The caller is responsible for deleting the returned object.
   std::shared_ptr<Song> CreateSong(std::string const& title,
                                 std::string const& interpreter,
                                 size_t const duration);

   std::shared_ptr<Album> CreateAlbum(std::string const& title,
                                      std::vector<std::shared_ptr<Song>> songs);

   std::shared_ptr<Collection> CreateCollection(std::string const& title,
                                                std::vector<std::shared_ptr<Media>> medias);
};
#endif //SIMPLEMEDIAFACTORY_H
