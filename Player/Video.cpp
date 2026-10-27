#include "Video.h"

Video::Video(std::string const& name, size_t const dur, VideoFormat const& format) :
    Media(name, dur),
    mFormat{ format }
{
}