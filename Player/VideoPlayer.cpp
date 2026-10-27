#include "VideoPlayer.h"

void VideoPlayer::Play() const
{
	//playing video number 1: Die Sendung mit der Maus [duration -> 55 min], AVI-Format
	std::count << "playing video number " << mIndex << ": " << mVideos.at(mIndex).mName
		<< "[duration -> " (mVideos.at(mIndex).mDuration / 60) << "min], "
		<< mVideos.at(mIndex).mFormat << "-Format" << std::cout;
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
	return false;
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


