#include "VideoPlayer.h"
#include <iostream>
#include <stdexcept>


void VideoPlayer::Play() const
{
	//intended format:
	//playing video number 1: Die Sendung mit der Maus [duration -> 55 min], AVI-Format
	std::cout << "playing video number " << mIndex << ": " << mVideos.at(mIndex).GetName()
		<< "[duration -> " << (mVideos.at(mIndex).GetDuration() / 60) << "min], "
		<< Video::FormatToString(mVideos.at(mIndex).GetFormat()) << "-Format" << std::endl;
}

void VideoPlayer::Stop() const
{
	//intended format:
	//stop video: Pulp Fiction [duration -> 126 min], MKV-Format
	std::cout << "stop video: " << mVideos.at(mIndex).GetName() << " "
		<< "[duration -> " << (mVideos.at(mIndex).GetDuration() / 60) << "min], "
		<< Video::FormatToString(mVideos.at(mIndex).GetFormat()) << "-Format" << std::endl;
}

bool VideoPlayer::First()
{
	if (mVideos.size() > 0)
	{
		mIndex = 0;
		return true;
	}
	else
	{
		throw std::invalid_argument("Playlist is empty.");
		return false;
	}
}

bool VideoPlayer::Next()
{
	if (!mVideos.empty())
	{
		if (mIndex < mVideos.size() - 1)
		{
			mIndex++;
			return true;
		}
		else
		{
			mIndex = 0; // playlist restarts from 0
			return false;
		}
	}
	else
	{
		throw std::invalid_argument("Cannot skip to next video: Empty playlist.");
		return false;
	}
}

size_t VideoPlayer::ActIndex() const
{
	return mIndex;
}

std::string const VideoPlayer::ActVideo() const
{
	return nullptr;
}

void VideoPlayer::SetVolume(uint8_t const vol)
{
	if (vol > 50)
	{
		throw std::invalid_argument("Wrong input: Choose Volume between 0 and 50.");
		return;
	}
	else
	{
		mVolume = vol;
		std::cout << "Volume set to " << vol << "." << std::endl;
	}
}

uint8_t VideoPlayer::GetVolume() const
{
	return mVolume;
}

void VideoPlayer::Add(std::string const& name, size_t const dur, VideoFormat const& format)
{
	mVideos.push_back({ name, dur, format });
}


