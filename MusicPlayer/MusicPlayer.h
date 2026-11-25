#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include "Object.h"

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
   void Search();

   /// @brief Adds a media to the playlist.
   ///
   /// Uses the factory to create the media.
   void Add();

   /// @brief Removes a media from the playlist.
   void Remove();

private:
   Media* mPlaylist;             ///< Playlist of the music player.
   SimpleMediaFactory* mFactory; ///< Factory to create media.
};
#endif //MUSICPLAYER_H
