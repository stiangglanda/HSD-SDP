#include "Video.h"

Video::Video(std::string const& name, size_t const dur, VideoFormat const& format) :
    Media(name, dur),
    mFormat{ format }
{
}

VideoFormat Video::GetFormat() const
{
    return mFormat;
}

std::string Video::FormatToString(VideoFormat format)
{
    switch (format)
    {
        case VideoFormat::AVI: return "AVI";
        case VideoFormat::MKV: return "MKV";
        case VideoFormat::WMV: return "WMV";
        default: return "NULL";
    }
}
