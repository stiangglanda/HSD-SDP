#ifndef VIDEO_H
#define VIDEO_H
#include "Media.h"

/// @author Julian Rieger
/// @date 27.10.2026
/// @brief The formats a video can have.
enum class VideoFormat
{
   MP4,
   AVI,
   MKV
};

/// @author Julian Rieger
/// @date 27.10.2026
/// @brief A video with a name, a duration and a format.
class Video : public Media
{
public:
   /// @brief Creates a video.
   /// @param[in] name is the name of the video.
   /// @param[in] dur is the duration of the video.
   /// @param[in] format is the format of the video.
   Video(std::string const& name, size_t const dur, VideoFormat const& format);

   /// @brief Returns mFormat
   VideoFormat GetFormat() const;

   static std::string FormatToString(VideoFormat format);

private:
	VideoFormat mFormat;

};

#endif //VIDEO_H
