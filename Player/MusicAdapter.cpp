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
    
}

void MusicAdapter::Select(std::string const& name)
{
    mMusicPlayer.Find(name);
}
