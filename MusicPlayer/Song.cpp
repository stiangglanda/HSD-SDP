#include "Song.h"
#include "Visitor.h"

Song::Song(std::string const& title, size_t const duration, std::string const& interpreter)
   : Publication(title, interpreter), mInterpreter(interpreter)
{
}

std::string const& Song::GetInterpreter() const
{
   return mInterpreter;
}

void Song::Accept(Visitor& visitor) const
{
	visitor.Visit(*this);
}

void Song::SetAlbum(Album* album)
{
   mAlbum = album;
}
