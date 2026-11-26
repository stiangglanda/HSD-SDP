#include "Album.h"
#include "Song.h"
#include "Visitor.h"
#include <utility>

Album::Album(std::string const& title, std::string const& interpreter, std::vector<std::shared_ptr<Song>> songs) : 
   Publication{title, interpreter}, mSongs{std::move(songs)}
{
   for (auto const& song : mSongs)
   {
      song->SetAlbum(this);
   }
}

size_t Album::GetNumSongs() const
{
   return mSongs.size();
}

size_t Album::GetDuration() const
{
   size_t duration = 0;
   for (auto const& song : mSongs)
   {
      duration += song->GetDuration();
   }
   return duration;
}

Media const* Album::GetChild(int const index) const
{
   if (index < 0 || static_cast<size_t>(index) >= mSongs.size())
   {
      return nullptr;
   }
   return mSongs[index].get();
}

void Album::Accept(Visitor& visitor) const
{
   visitor.Visit(*this);
}
