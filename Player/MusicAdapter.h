#ifndef MUSICADAPTER_H
#define MUSICADAPTER_H
#include "Object.h"
#include "Player.h"
#include "MusicPlayer.h"

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief Makes the MusicPlayer usable as a Player.
class MusicAdapter : public Object, public Player
{
public:
   /// @brief Constructs a new MusicAdapter.
   /// @param[in] player is the MusicPlayer to adapt.
   explicit MusicAdapter(MusicPlayer& player);
   
   /// @brief Starts playing.
   void Play() override;

   /// @brief Increases the volume.
   void VolInc() override;

   /// @brief Decreases the volume.
   void VolDec() override;

   /// @brief Stops playing.
   void Stop() override;

   /// @brief Switches to the next song.
   void Next() override;

   /// @brief Switches to the previous song.
   void Prev() override;

   /// @brief Selects a song by its name.
   /// @param[in] name is the name of the song.
   void Select(std::string const& name) override;

private:
   MusicPlayer& mMusicPlayer;
};

#endif //MUSICADAPTER_H