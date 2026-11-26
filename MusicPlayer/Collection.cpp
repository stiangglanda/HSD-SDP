#include "Collection.h"
#include "Visitor.h"

#include <algorithm>

Collection::Collection(std::string const& title)
   : Media(title)
{
}

size_t Collection::GetNumSongs() const
{
   size_t c = 0;
   for(auto const& e : mMedias)
   {
      
   }
}

size_t Collection::GetDuration() const
{
   size_t duration = 0;
   for (auto const media : mMedias)
   {
      duration += media->GetDuration();
   }
   return duration;
}

void Collection::Add(Media* media)
{
   mMedias.push_back(media);
}

void Collection::Remove(Media* media)
{
   auto It = std::find(mMedias.begin(), mMedias.end(), media);
   if(It != mMedias.end())
   {
      mMedias.erase(It);
   }
}

Media const* Collection::GetChild(int const index) const
{
   if (index < 0 || static_cast<size_t>(index) >= mMedias.size())
   {
      return nullptr;
   }
   return mMedias[index];
}

void Collection::Accept(Visitor& visitor) const
{
   visitor.Visit(*this);
}
