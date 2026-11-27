#include "VisitorSearch.h"
#include <iostream>
#include <stdexcept>
#include "Album.h"
#include "Collection.h"
#include "Song.h"

VisitorSearch::VisitorSearch(std::string const& searchTerm)
   : mSearchTerm(searchTerm)
{
   if (mSearchTerm.empty())
   {
      throw std::invalid_argument("Search term must not be empty");
   }
}

void VisitorSearch::Check(std::string const& title) const
{
   if (title.find(mSearchTerm) != std::string::npos)
   {
      std::cout << title << '\n';
   }
}

void VisitorSearch::Visit(Collection const& collection)
{
   Check(collection.GetTitle());
   for (int i = 0; collection.GetChild(i) != nullptr; ++i)
   {
      collection.GetChild(i)->Accept(*this);
   }
}

void VisitorSearch::Visit(Song const& song)
{
   Check(song.GetTitle());
}

void VisitorSearch::Visit(Album const& album)
{
   Check(album.GetTitle());
   for (int i = 0; album.GetChild(i) != nullptr; ++i)
   {
      album.GetChild(i)->Accept(*this);
   }
}
