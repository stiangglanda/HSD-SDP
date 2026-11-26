#include "Album.h"
#include "Song.h"
#include "Visitor.h"

Album::AlbumAlbum(std::string const& title, std::string const& interpreter, std::vector<std::shared_ptr<Song>> songs)
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
