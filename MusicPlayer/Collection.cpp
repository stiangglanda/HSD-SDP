#include "Collection.h"
#include "Visitor.h"
#include "Album.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace
{
   // Returns true if target is root itself or is contained somewhere below root.
   bool Contains(Media const& root, Media const* const target)
   {
      if (&root == target)
      {
         return true;
      }
      for (int i = 0; root.GetChild(i) != nullptr; ++i)
      {
         if (Contains(*root.GetChild(i), target))
         {
            return true;
         }
      }
      return false;
   }
}

Collection::Collection(std::string const& title)
   : Media(title)
{
}

size_t Collection::GetNumSongs() const
{
   size_t count = 0;
   for (auto const& media : mMedias)
   {
      Album const* const album = dynamic_cast<Album const*>(media.get());
      Collection const* const collection = dynamic_cast<Collection const*>(media.get());
      if (album != nullptr)
      {
         count += album->GetNumSongs();
      }
      else if (collection != nullptr)
      {
         count += collection->GetNumSongs();
      }
      else
      {
         ++count;
      }
   }
   return count;
}

size_t Collection::GetDuration() const
{
   size_t duration = 0;
   for (auto const& media : mMedias)
   {
      duration = AddDuration(duration, media->GetDuration());
   }
   return duration;
}

void Collection::Add(std::shared_ptr<Media> media)
{
   if (media == nullptr)
   {
      throw std::invalid_argument("Media is a null pointer");
   }
   if (Contains(*media, this))
   {
      throw std::invalid_argument("Collection must not contain itself");
   }
   mMedias.push_back(std::move(media));
}

bool Collection::Remove(std::string const& title)
{
   auto const it = std::find_if(mMedias.cbegin(), mMedias.cend(),
                                [&title](std::shared_ptr<Media> const& media)
                                {
                                   return media->GetTitle() == title;
                                });
   if (it != mMedias.cend())
   {
      mMedias.erase(it);
      return true;
   }

   for (auto const& media : mMedias)
   {
      Collection* const collection = dynamic_cast<Collection*>(media.get());
      if (collection != nullptr && collection->Remove(title))
      {
         return true;
      }
   }
   return false;
}

Media const* Collection::GetChild(int const index) const
{
   if (index < 0 || static_cast<size_t>(index) >= mMedias.size())
   {
      return nullptr;
   }
   return mMedias[static_cast<size_t>(index)].get();
}

void Collection::Accept(Visitor& visitor) const
{
   visitor.Visit(*this);
}
