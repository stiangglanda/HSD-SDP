#include "MusicPlayer.h"
#include <algorithm>
#include <iostream>

void MusicPlayer::Start() {
    std::cout << "Start " << mSongs[mIndex].GetName() << std::endl;
}

void MusicPlayer::Stop() {
    std::cout << "Stop " << mSongs[mIndex].GetName() << std::endl;
}

void MusicPlayer::SwitchNext() {
    if(mIndex >= mSongs.size()) {
        mIndex = 0;
    } else {
        mIndex++;
    }
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
        return false;
    }

    mIndex = static_cast<size_t>(std::distance(mSongs.begin(), it));
    return true;
}

size_t MusicPlayer::GetCount() const {
    return mSongs.size();
}

void MusicPlayer::IncreaseVol(size_t const vol) {
    if (mVolume+vol >= 100) {
        mVolume = 100;
    }
    else {
        mVolume += vol;
    }
    return;
}

void MusicPlayer::DecreaseVol(size_t const vol) {
    if (mVolume-vol <= 0) {
        mVolume = 0;
    }
    else {
        mVolume -= vol;
    }
    return;
}

void MusicPlayer::Add(std::string const& name, size_t const dur) {
    mSongs.push_back({name, dur});
}