#include "MusicPlayer.h"
#include <algorithm>
#include "Media.h"
#include "SimpleMediaFactory.h"
#include "VisitorSearch.h"

void MusicPlayer::Play()
{
    VisitorPlay mVisitor;
    for (const auto& media : mPlaylist)
    {
        media->Accept(mVisitor);
    }
}

void MusicPlayer::Search(std::string const& searchTerm)
{
    VisitorSearch mVisitor{searchTerm};
    for (const auto& media : mPlaylist)
    {
        media->Accept(mVisitor);
    }
}

void MusicPlayer::Add(MediaKind kind,
                      std::string const& title,
                      size_t const duration,
                      std::string const& interpreter)
{
    auto media = mFactory.CreateMedia(kind, title, duration, interpreter);
    if (media != nullptr)
    {
        mPlaylist.push_back(std::move(media));
    }
}

void MusicPlayer::Remove()
{
    auto media = mFactory.CreateMedia(MediaKind::Album, "All Along the Watchtower", "AC/DC");
    media->
}
