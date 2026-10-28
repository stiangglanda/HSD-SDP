#include "VideoPlayer.h"
#include <iostream>
#include <stdexcept>


void VideoPlayer::Play() const {
    if (mVideos.empty()) {
        std::cout << "no video in playlist!" << std::endl;
        return;
    }
    const auto& vid = mVideos.at(mIndex);
    std::cout << "playing video number " << (mIndex + 1) << ": " << vid.GetName()
              << " [duration -> " << vid.GetDuration() << " min], "
              << Video::FormatToString(vid.GetFormat()) << "-Format" << std::endl;
}

void VideoPlayer::Stop() const {
    if (mVideos.empty()) {
        std::cout << "no video in playlist!" << std::endl;
        return;
    }
    const auto& vid = mVideos.at(mIndex);
    std::cout << "stop video: " << vid.GetName()
              << " [duration -> " << vid.GetDuration() << " min], "
              << Video::FormatToString(vid.GetFormat()) << "-Format" << std::endl;
}

bool VideoPlayer::First() {
    if (mVideos.empty()) {
        return false;
    }
    mIndex = 0;
    return true;
}

bool VideoPlayer::Next() {
    if (mVideos.empty() || mIndex + 1 >= mVideos.size()) {
        return false;
    }
    mIndex++;
    return true;
}

size_t VideoPlayer::ActIndex() const
{
	return mIndex;
}

std::string const VideoPlayer::ActVideo() const
{
	return mVideos.at(mIndex).GetName();
}
void VideoPlayer::SetVolume(size_t const vol) {
    if (vol > 50) {
        mVolume = 50;
    } else {
        mVolume = vol;
    }
    std::cout << "volume is now -> " << mVolume << std::endl;
}

size_t VideoPlayer::GetVolume() const
{
	return mVolume;
}

void VideoPlayer::Add(std::string const& name, size_t const dur, VideoFormat const& format)
{
	mVideos.push_back({ name, dur, format });
}

