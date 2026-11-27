#include "MusicPlayer.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "Collection.h"
#include "Media.h"
#include "VisitorPlay.h"
#include "VisitorSearch.h"

void MusicPlayer::Play() const
{
   VisitorPlay visitor;
   for (auto const& media : mPlaylist)
   {
      media->Accept(visitor);
   }
}

void MusicPlayer::Search(std::string const& searchTerm) const
{
   VisitorSearch visitor{searchTerm};
   std::cout << "search for \"" << searchTerm << "\": found medias:\n";
   for (auto const& media : mPlaylist)
   {
      media->Accept(visitor);
   }
}

void MusicPlayer::Add(std::shared_ptr<Media> media)
{
   if (media == nullptr)
   {
      throw std::invalid_argument("Media is a null pointer");
   }
   mPlaylist.push_back(std::move(media));
}

bool MusicPlayer::Remove(std::string const& title)
{
   auto const it = std::find_if(mPlaylist.cbegin(), mPlaylist.cend(),
                                [&title](std::shared_ptr<Media> const& media)
                                {
                                   return media->GetTitle() == title;
                                });
   if (it != mPlaylist.cend())
   {
      mPlaylist.erase(it);
      return true;
   }

   for (auto const& media : mPlaylist)
   {
      Collection* const collection = dynamic_cast<Collection*>(media.get());
      if (collection != nullptr && collection->Remove(title))
      {
         return true;
      }
   }
   return false;
}
