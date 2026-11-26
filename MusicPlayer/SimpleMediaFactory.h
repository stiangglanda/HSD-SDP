#ifndef SIMPLEMEDIAFACTORY_H
#define SIMPLEMEDIAFACTORY_H
#include <memory>
#include <string>

class Media;

enum class MediaKind { Song, Album, Collection };

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
   std::unique_ptr<Media> CreateMedia(MediaKind kind, std::string const& title, size_t const duration, std::string const& interpreter);
};
#endif //SIMPLEMEDIAFACTORY_H
