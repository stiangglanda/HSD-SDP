#include "VideoPlayer.h"

void VideoPlayer::Play() const
{
}

void VideoPlayer::Stop() const
{
}

bool VideoPlayer::First()
{
	return false;
}

bool VideoPlayer::Next()
{

}

size_t VideoPlayer::ActIndex() const
{
	return size_t();
}

std::string const VideoPlayer::ActVideo() const
{
	return nullptr;
}

void VideoPlayer::SetVolume(size_t const vol)
{
}

size_t VideoPlayer::GetVolume() const
{
	return size_t();
}

void VideoPlayer::Add(std::string const& name, size_t const dur, VideoFormat const& format)
{
}


