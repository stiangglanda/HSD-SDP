#ifndef VIDEOADAPTER_H
#define VIDEOADAPTER_H
#include "Object.h"
#include "Player.h"
#include "VideoPlayer.h"

/// @author Julian Rieger
/// @date 27.10.2026
/// @brief Makes the VideoPlayer usable as a Player.
class VideoAdapter : public Object, public Player
{
public:
   /// @brief Constructs a new VideoAdapter.
   /// @param[in] player is the VideoPlayer to adapt.
   explicit VideoAdapter(VideoPlayer& player);

   /// @brief Starts playing.
   void Play() override;

   /// @brief Increases the volume.
   void VolInc() override;

   /// @brief Decreases the volume.
   void VolDec() override;

   /// @brief Stops playing.
   void Stop() override;

   /// @brief Switches to the next video.
   void Next() override;

   /// @brief Switches to the previous video.
   void Prev() override;

   /// @brief Selects a video by its name.
   /// @param[in] name is the name of the video.
   void Select(std::string const& name) override;

private:
	VideoPlayer& mVideoPlayer;
};

#endif //VIDEOADAPTER_H
