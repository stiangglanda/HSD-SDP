#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H
#include <cstddef>
#include <string>
#include <vector>
#include "Video.h"

/// @author Julian Rieger
/// @date 27.10.2026
/// @brief Plays videos from a list.
class VideoPlayer
{
public:
   /// @brief Starts playing the current video.
   void Play() const;

   /// @brief Stops playing.
   void Stop() const;

   /// @brief Selects the first video.
   /// @return true if there is a first video.
   bool First();

   /// @brief Selects the next video.
   /// @return true if there is a next video.
   bool Next();

   /// @brief Gets the index of the current video.
   /// @return the index of the current video.
   size_t ActIndex() const;

   /// @brief Gets the name of the current video.
   /// @return the name of the current video.
   std::string const ActVideo() const;

   /// @brief Sets the volume.
   /// @param[in] vol is the new volume.
   void SetVolume(size_t const vol);

   /// @brief Gets the volume.
   /// @return the current volume.
   size_t GetVolume() const;

   /// @brief Adds a video to the list.
   /// @param[in] name is the name of the video.
   /// @param[in] dur is the duration of the video.
   /// @param[in] format is the format of the video.
   void Add(std::string const& name, size_t const dur, VideoFormat const& format);

   static constexpr size_t defVolume = 8;
   static constexpr size_t maxVolume = 50;
   
private:
	std::vector<Video> mVideos;
   size_t mIndex{ 0 };
   size_t mVolume{ defVolume };
};

#endif //VIDEOPLAYER_H
