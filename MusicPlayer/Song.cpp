#include "Song.h"
#include "Visitor.h"

Song::Song(std::string const& title, std::string const& interpreter, size_t const duration)
   : Publication(title, interpreter), mDuration(duration)
{
}

size_t Song::GetDuration() const
{
   return mDuration;
}

void Song::Accept(Visitor& visitor) const
{
	visitor.Visit(*this);
}

void Song::SetAlbum(Album* album)
{
   mAlbum = album;
}
