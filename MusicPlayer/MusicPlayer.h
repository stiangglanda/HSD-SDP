#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <memory>
#include <string>
#include <vector>

#include "Object.h"

class Media;

/// @author Leander Kieweg
/// @date 25.11.2026
/// @brief Concrete class for a music player.
///
/// The class manages a playlist of media and plays or searches it with visitors.
class MusicPlayer : public Object
{
public:
   /// @brief Plays the playlist.
   ///
   /// Uses a VisitorPlay to print all media to std::cout.
   void Play() const;

   /// @brief Searches in the playlist.
   /// @param[in] searchTerm is the term to search for in the titles.
   /// @throws std::invalid_argument if the search term is empty.
   ///
   /// Uses a VisitorSearch to print all media whose title contains the search term.
   void Search(std::string const& searchTerm) const;

   /// @brief Adds a media to the end of the playlist.
   /// @param[in] media is the media to add.
   /// @throws std::invalid_argument if the media is a null pointer.
   void Add(std::shared_ptr<Media> media);

   /// @brief Removes a media from the playlist.
   /// @param[in] title is the title of the media to remove.
   /// @returns true if a media was removed, otherwise false.
   ///
   /// Removes the first media with the given title. If there is none in the
   /// playlist, the collections of the playlist are searched (also nested ones).
   bool Remove(std::string const& title);

private:
   std::vector<std::shared_ptr<Media>> mPlaylist;  ///< Media of the playlist (*).
};
#endif //MUSICPLAYER_H
