#ifndef SIMPLEMEDIAFACTORY_H
#define SIMPLEMEDIAFACTORY_H
#include <string>

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
   Media* CreateMedia(std::string const& kind);
};
#endif //SIMPLEMEDIAFACTORY_H
