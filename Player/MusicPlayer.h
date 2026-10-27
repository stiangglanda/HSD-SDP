#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H
#include <cstddef>
#include <string>
#include <vector>
#include "Song.h"

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief Plays songs from a list.
class MusicPlayer
{
private:
   size_t mVolume;
   size_t mIndex;
   std::vector<Song> mSongs;

public:
   /// @brief Starts playing the current song.
   void Start();

   /// @brief Stops playing.
   void Stop();

   /// @brief Switches to the next song.
   void SwitchNext();

   /// @brief Gets the index of the current song.
   /// @return the index of the current song.
   size_t GetActIndex() const;

   /// @brief Searches a song by its name and selects it.
   /// @param[in] name is the name of the song.
   /// @return true if the song was found.
   bool Find(std::string const& name);

   /// @brief Gets the number of songs.
   /// @return the number of songs.
   size_t GetCount() const;

   /// @brief Increases the volume.
   /// @param[in] vol is the value to increase by.
   void IncreaseVol(size_t const vol);

   /// @brief Decreases the volume.
   /// @param[in] vol is the value to decrease by.
   void DecreaseVol(size_t const vol);

   /// @brief Adds a song to the list.
   /// @param[in] name is the name of the song.
   /// @param[in] dur is the duration of the song.
   void Add(std::string const& name, size_t const dur);
};

#endif //MUSICPLAYER_H
