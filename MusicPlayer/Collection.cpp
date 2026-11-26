#include "Collection.h"
#include "Visitor.h"

#include <algorithm>

Collection::Collection(std::string const& title)
   : Media(title)
{
}

size_t Collection::GetNumSongs() const
{
   return mMedias.size();
}

void Collection::Add(Media* media)
{
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
   return nullptr;
}

void Collection::Accept(Visitor& visitor) const
{
   visitor.Visit(*this);
}
