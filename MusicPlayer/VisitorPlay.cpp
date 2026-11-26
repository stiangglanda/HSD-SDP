#include "VisitorPlay.h"
#include <iostream>
#include "Collection.h"
#include "Song.h"
#include "Album.h"

void VisitorPlay::Visit(Collection const& collection)
{
    std::cout << "Collection: " << collection.GetTitle() << " (" << collection.GetNumSongs() << " Songs) << " << collection.GetDuration() << std::endl;
    
    for (int i = 0; collection.GetChild(i) != nullptr; ++i)
    {
        collection.GetChild(i)->Accept(*this);
    }
}

void VisitorPlay::Visit(Song const& song)
{
    std::cout << "1. " << song.GetTitle() << " << " << song.GetDuration() << " << " << song.GetInterpreter() << std::endl;;
}

void VisitorPlay::Visit(Album const& album)
{
    std::cout << "Album: " << album.GetTitle() << " (" << album.GetNumSongs() << " Songs) << " << album.GetDuration() << std::endl;

    for (int i = 0; album.GetChild(i) != nullptr; ++i)
    {
        album.GetChild(i)->Accept(*this);
    }
}
