#include "Album.h"
#include "Song.h"
#include "Visitor.h"
#include <stdexcept>
#include <utility>

Album::Album(std::string const& title, std::string const& interpreter, std::vector<std::shared_ptr<Song>> songs) :
   Publication{title, interpreter}, mSongs{std::move(songs)}
{
   if (mSongs.empty())
   {
      throw std::invalid_argument("Album must contain at least one song");
   }
   for (auto const& song : mSongs)
   {
      if (song == nullptr)
      {
         throw std::invalid_argument("Song of album is a null pointer");
      }
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
      duration = AddDuration(duration, song->GetDuration());
   }
   return duration;
}

Media const* Album::GetChild(int const index) const
{
   if (index < 0 || static_cast<size_t>(index) >= mSongs.size())
   {
      return nullptr;
   }
   return mSongs[static_cast<size_t>(index)].get();
}

void Album::Accept(Visitor& visitor) const
{
   visitor.Visit(*this);
}
