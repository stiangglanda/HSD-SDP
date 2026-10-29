#include "VideoAdapter.h"
#include <iostream>

VideoAdapter::VideoAdapter(VideoPlayer& player) : mVideoPlayer{ player } {

}

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
    if (vol < VideoPlayer::maxVolume) {
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
}

void VideoAdapter::Prev() {
    if (mVideoPlayer.ActIndex() > 0) {
        size_t targetIndex = mVideoPlayer.ActIndex() - 1;
        mVideoPlayer.First();
        for (size_t i = 0; i < targetIndex; ++i) {
            mVideoPlayer.Next();
        }
    }
}

void VideoAdapter::Select(std::string const& name) {
    if (!mVideoPlayer.First()) {
        std::cerr << "video: " << name << " not found!" << std::endl;
        return;
    }

    do {
        if (mVideoPlayer.ActVideo() == name) {
            Play();
            return;
        }
    } while (mVideoPlayer.Next());

    std::cerr << "video: " << name << " not found!" << std::endl;
}
