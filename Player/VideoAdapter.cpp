#include "VideoAdapter.h"
#include <stdexcept>

void VideoAdapter::Play()
{
	mVideoPlayer.Play();
}

void VideoAdapter::VolInc()
{
	//exception handling in videoplayer.cpp
	uint8_t vol = mVideoPlayer.GetVolume();
	vol += 1;
	mVideoPlayer.SetVolume(vol);
}

void VideoAdapter::VolDec()
{
	//exception handling in videoplayer.cpp
	uint8_t vol = mVideoPlayer.GetVolume();
	vol -= 1;
	mVideoPlayer.SetVolume(vol);
}

void VideoAdapter::Stop()
{
	mVideoPlayer.Stop();
}

void VideoAdapter::Next()
{
	mVideoPlayer.Next();
	Play();
}

void VideoAdapter::Prev()
{
	size_t prevIndex = mVideoPlayer.ActIndex();
	if (prevIndex != 0)
	{
		prevIndex -= 1;
		while (mVideoPlayer.ActIndex() != prevIndex)
		{
			mVideoPlayer.Next();
		}
		Play();
	}
	else
	{
		throw std::invalid_argument("Cannot play previous Video because Index is 0.");
	}
}

void VideoAdapter::Select(std::string const& name)
{
	size_t playlistSize = GetSize();

	//iterate through all videos and compare name
	for(size_t i = 0; i < playlistSize; i++)
	{
		if (mVideoPlayer.ActVideo() == name)
		{
			Play();
			return;
		}
	}
	throw std::invalid_argument("Cannot find the given title in playlist.");
}

size_t VideoAdapter::GetSize()
{
	size_t currIndex = mVideoPlayer.ActIndex();
	size_t playlistSize = 0;

	// skips to next song in playlist
	mVideoPlayer.Next();
	
	//find playlist size to iterate through all videos
	while (currIndex != mVideoPlayer.ActIndex())
	{
		mVideoPlayer.Next();
		playlistSize++;
	}

	return playlistSize;
}
