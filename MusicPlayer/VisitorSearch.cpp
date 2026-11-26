#include "VisitorSearch.h"

#include <iostream>
#include <ostream>

#include "Collection.h"
#include "Song.h"
#include "Album.h"

VisitorSearch::VisitorSearch(std::string const& searchTerm)
    : mSearchTerm(searchTerm)
{
    std::cout << "search for \""<< mSearchTerm <<"\": found medias:" << std::endl;
}

void VisitorSearch::Visit(Collection const& collection)
{
    if (collection.GetTitle().find(mSearchTerm) != std::string::npos)
    {
        std::cout << collection.GetTitle() << std::endl;
    }

    for (int i = 0; collection.GetChild(i) != nullptr; ++i)
    {
        collection.GetChild(i)->Accept(*this);
    }
}

void VisitorSearch::Visit(Song const& song)
{
    if (song.GetTitle().find(mSearchTerm) != std::string::npos)
    {
        std::cout << song.GetTitle() << std::endl;
    }
}

void VisitorSearch::Visit(Album const& album)
{
    if (album.GetTitle().find(mSearchTerm) != std::string::npos)
    {
        std::cout << album.GetTitle() << std::endl;
    }
    
    for (int i = 0; album.GetChild(i) != nullptr; ++i)
    {
        album.GetChild(i)->Accept(*this);
    }
}
