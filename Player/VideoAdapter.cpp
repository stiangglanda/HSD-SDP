#include "VideoAdapter.h"
#include <stdexcept>

void VideoAdapter::Play()
{
	mVideoPlayer.Play();
}

void VideoAdapter::VolDec() {
    size_t vol = mVideoPlayer.GetVolume();
    if (vol > 0) {
        mVideoPlayer.SetVolume(vol - 1);
    }
}

void VideoAdapter::VolInc() {
    size_t vol = mVideoPlayer.GetVolume();
    if (vol < 50) {
        mVideoPlayer.SetVolume(vol + 1);
    }
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

void VideoAdapter::Select(std::string const& name) {
    if (!mVideoPlayer.First()) {
        std::cout << "video: " << name << " not found!" << std::endl;
        return;
    }

    do {
        if (mVideoPlayer.ActVideo() == name) {
            Play();
            return;
        }
    } while (mVideoPlayer.Next());

    std::cout << "video: " << name << " not found!" << std::endl;
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
