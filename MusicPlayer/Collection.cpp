#include "Collection.h"
#include "Visitor.h"
#include "Album.h"

#include <algorithm>
#include <utility>

Collection::Collection(std::string const& title)
   : Media(title)
{
}

size_t Collection::GetNumSongs() const
{
   size_t c = 0;
   for (auto const& e : mMedias)
   {
      std::shared_ptr<Album> album = std::dynamic_pointer_cast<Album>(e);
      std::shared_ptr<Collection> collection = std::dynamic_pointer_cast<Collection>(e);
      if (album != nullptr)
      {
         c += album->GetNumSongs();
      }
      else if (collection != nullptr)
      {
         c += collection->GetNumSongs();
      }
      else
      {
         ++c;
      }
   }
   return c;
}

size_t Collection::GetDuration() const
{
   size_t duration = 0;
   for (auto const& media : mMedias)
   {
      duration += media->GetDuration();
   }
   return duration;
}

void Collection::Add(std::shared_ptr<Media> media)
{
   if (media != nullptr)
   {
      mMedias.push_back(std::move(media));
   }
}

bool Collection::Remove(std::string const& title)
{
   auto It = std::find_if(mMedias.begin(), mMedias.end(), [&title](std::shared_ptr<Media> const& media)
                           {
                              return media->GetTitle() == title;
                           });
   if(It != mMedias.end())
   {
      mMedias.erase(It);
      return true;
   }
   return false;
}

Media const* Collection::GetChild(int const index) const
{
   if (index < 0 || static_cast<size_t>(index) >= mMedias.size())
   {
      return nullptr;
   }
   return mMedias[index].get();
}

void Collection::Accept(Visitor& visitor) const
{
   visitor.Visit(*this);
}
