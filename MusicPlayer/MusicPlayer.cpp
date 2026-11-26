#include "MusicPlayer.h"
#include <algorithm>
#include "Collection.h"
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

void MusicPlayer::Add(std::shared_ptr<Media> media) {
    if (media != nullptr)
    {
        mPlaylist.push_back(std::move(media));
    }
}

void MusicPlayer::Remove(std::string const& title)
{
    auto it = std::find_if(mPlaylist.begin(), mPlaylist.end(),
                           [&title](std::shared_ptr<Media> const& media)
                           {
                              return media->GetTitle() == title;
                           });
    if (it != mPlaylist.end())
    {
        mPlaylist.erase(it);
        return;
    }

    for (auto const& media : mPlaylist)
    {
        auto collection = std::dynamic_pointer_cast<Collection>(media);
        if (collection != nullptr && collection->Remove(title))
        {
            return;
        }
    }
}
