#ifndef VIDEO_H
#define VIDEO_H
#include "Media.h"

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief The formats a video can have.
enum class VideoFormat
{
   MP4,
   AVI,
   MKV
};

/// @author Leander Kieweg
/// @date 27.10.2026
/// @brief A video with a name, a duration and a format.
class Video : public Media
{
private:
   VideoFormat mFormat;

public:
   /// @brief Creates a video.
   /// @param[in] name is the name of the video.
   /// @param[in] dur is the duration of the video.
   /// @param[in] format is the format of the video.
   Video(std::string const& name, size_t const dur, VideoFormat const& format);
};

#endif //VIDEO_H
