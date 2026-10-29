#include "MusicPlayer.h"
#include <algorithm>
#include <iostream>

void MusicPlayer::Start() {
    if (mSongs.empty()) {
        std::cerr << "no song in playlist!" << std::endl;
        return;
    }

    if (mIndex >= mSongs.size()) {
        mIndex = 0;
    }

    const Song& song = mSongs[mIndex];
    std::cout << "playing song number " << mIndex + 1 << ": "
              << song.GetName() << " (" << song.GetDuration() << " sec)"
              << std::endl;
}

void MusicPlayer::Stop() {
    if (mSongs.empty()) {
        std::cerr << "no song in playlist!" << std::endl;
        return;
    }

    if (mIndex >= mSongs.size()) {
        mIndex = 0;
    }

    const Song& song = mSongs[mIndex];
    std::cout << "stop song: " << song.GetName() << " ("
              << song.GetDuration() << " sec)" << std::endl;
}

void MusicPlayer::SwitchNext() {
    if (mSongs.empty()) {
        return;
    }

    mIndex = (mIndex + 1) % mSongs.size();
}

size_t MusicPlayer::GetActIndex() const {
    return mIndex;
}

bool MusicPlayer::Find(std::string const& name) {
    auto it = std::ranges::find_if(mSongs,
        [&name](Song const& song) {
            return song.GetName() == name;
        });

    if (it == mSongs.end()) {
        std::cerr << "song: " << name << " not found!" << std::endl;
        return false;
    }

    mIndex = static_cast<size_t>(std::distance(mSongs.begin(), it));
    return true;
}

size_t MusicPlayer::GetCount() const {
    return mSongs.size();
}

void MusicPlayer::IncreaseVol(size_t const vol) {
    if (vol >= maxVolume - mVolume) {
        mVolume = maxVolume;
    }
    else {
        mVolume += vol;
    }
    std::cout << "volume is now -> " << mVolume << std::endl;
}

void MusicPlayer::DecreaseVol(size_t const vol) {
    if (vol >= mVolume) {
        mVolume = minVolume;
    }
    else {
        mVolume -= vol;
    }
    std::cout << "volume is now -> " << mVolume << std::endl;
}

void MusicPlayer::Add(std::string const& name, size_t const dur) {
    mSongs.push_back({name, dur});
}