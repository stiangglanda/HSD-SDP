#include "MusicAdapter.h"

void MusicAdapter::Play()
{
    mMusicPlayer.Start();
}

void MusicAdapter::VolInc()
{
    mMusicPlayer.IncreaseVol(1);
}

void MusicAdapter::VolDec()
{
    mMusicPlayer.DecreaseVol(1);
}

void MusicAdapter::Stop()
{
    mMusicPlayer.Stop();
}

void MusicAdapter::Next()
{
    mMusicPlayer.SwitchNext();
}

void MusicAdapter::Prev()
{
    const size_t count = mMusicPlayer.GetCount();
    if (count == 0) {
        return;
    }

    const size_t current = mMusicPlayer.GetActIndex();
    size_t target = count - 1;
    if (current > 0 && current < count) {
        target = current - 1;
    }

    while (mMusicPlayer.GetActIndex() != target) {
        mMusicPlayer.SwitchNext();
    }
}

void MusicAdapter::Select(std::string const& name)
{
    mMusicPlayer.Find(name);
}
