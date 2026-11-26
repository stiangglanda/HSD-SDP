#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <memory>
#include <vector>

#include "Object.h"
#include "SimpleMediaFactory.h"
#include "VisitorPlay.h"

class Media;
class SimpleMediaFactory;

/// @author Leander Kieweg
/// @date 25.11.2026
/// @brief Concrete class for a music player.
///
/// The class manages a playlist and uses a factory to create media.
class MusicPlayer : public Object
{
public:
   /// @brief Plays the playlist.
   ///
   /// Uses a visitor to play all media.
   void Play();

   /// @brief Searches in the playlist.
   ///
   /// Uses a visitor to search all media.
   void Search(std::string const& searchTerm);

   /// @brief Adds a media to the playlist.
   ///
   /// Uses the factory to create the media.
   void Add(std::shared_ptr<Media> media);
   
   /// @brief Removes a media from the playlist.
   void Remove(std::string const& title);

private:
   std::vector<std::shared_ptr<Media>> mPlaylist;
};
#endif //MUSICPLAYER_H
