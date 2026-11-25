#include "Album.h"
#include "Song.h"
#include "Visitor.h"

Album::Album(std::string const& title, size_t const duration)
   : Media(title, duration)
{
}

size_t Album::GetNumSongs() const
{
   return 0;
}

Media const* Album::GetChild(int const index) const
{
   return nullptr;
}

void Album::Accept(Visitor& visitor) const
{
}
